/**
 * AdvertCast
 *
 * Piotr Rżysko
 * 27.12.2015
 */

#include "UDPClient.hpp"

UDPClient::UDPClient(std::string multicastAddr, std::string port, ClientController *parent) : parent(parent)
{
    if (initClient(multicastAddr, port))
    {
        logger::info << "Klient UDP zostal uruchomiony.\n";
        startVideoFilesManage();
    } else
    {
        logger::error << "Wystapil blad podczas uruchamiania klienta UDP.\n";
    }
}

void UDPClient::start()
{
    Parser datagramParser;
    char buffer[MAX_DATAGRAM_SIZE];

    while(true)
    {
        memset(buffer, 0, sizeof(buffer));
        ssize_t bytesRec = 0;
        if ((bytesRec = recvfrom(sockfd, buffer, sizeof(buffer), 0, NULL, 0)) == -1)
        {
            // TODO: obsluzyc
        } else
        {
            std::string bufferStr(buffer, bytesRec);
            uint fileId, number;
            std::string data;
            bool isLast = false, wrongDatagram = false;

            if (!datagramParser.matchMiddle(bufferStr, fileId, number, data))
            {
                if (!datagramParser.matchBegin(bufferStr, fileId, number, data))
                {
                    if (datagramParser.matchEnd(bufferStr, fileId, number, data))
                    {
                        isLast = true;
                    } else
                    {
                        wrongDatagram  = true;
                    }
                }
            }
            if (!wrongDatagram)
            {
                logger::info << "Received: datagram_num = [" << number << "] file_id = [" << fileId << "].\n";
                mutex_files.lock();
                std::map<uint, ReceivedVideoFile>::iterator it = videoFiles.find(fileId);
                if (it != videoFiles.end())
                {
                    it->second.addData(number, data, isLast);
                } else
                {
                    ReceivedVideoFile file;
                    file.addData(number, data, isLast);
                    videoFiles[fileId] = file;
                    it = videoFiles.find(fileId);
                }
                if (it->second.isFull())
                {
                    std::string filePath = "./test_" + std::to_string(it->first);
                    it->second.writeToFile(filePath);
                    videoFiles.erase(it);
                    logger::info << "Saved: file_id = [" << fileId << "] to file = [" << filePath << "].\n";
                }
                mutex_files.unlock();
            } else
            {
                logger::error << "Wrong datagram.\n";
            }
        }
    }

}

bool UDPClient::initClient(std::string multicastAddr, std::string port)
{
    SocketFactory socketFactory;
    MulticastUtils multicastUtils;
    struct sockaddr_storage addr;

    memset(&addr, 0, sizeof(addr));
    sockfd = socketFactory.createSocket(multicastAddr, port, AF_UNSPEC, SOCK_DGRAM, &addr, false);
    if (sockfd == -1)
    {
        perror("createSocket error::");
        logger::error << "createSocket error::\n";
        return false;
    }

    u_int yes=1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) < 0)
    {
        logger::error << "Reusing ADDR failed\n";
        return false;
    }

    if (!multicastUtils.joinMulticastGroup(sockfd, &addr))
    {
        logger::error << "joinMulticastGroup error::\n";
        close(sockfd);
        return false;
    }

    return true;
}

void UDPClient::startVideoFilesManage()
{
    std::thread t1(&UDPClient::manageVideoFiles, this,  MANAGE_VIDEO_FILES_INTERVAL);
    t1.detach();
}

void UDPClient::manageVideoFiles(uint interval)
{
    while(true)
    {
        mutex_files.lock();
        std::vector<uint> fileIds;
        std::map<uint, ReceivedVideoFile>::iterator it;
        for (it = videoFiles.begin(); it != videoFiles.end();)
        {
            if (it->second.isExpired())
            {
                fileIds.push_back(it->first);
                logger::warn << "File is expired: file_id = [" << it->first << "]\n";
                it = videoFiles.erase(it);
            }
            else
            {
                ++it;
            }
        }
        mutex_files.unlock();
        parent->sendNAKs(fileIds);
        std::this_thread::sleep_for (std::chrono::seconds(interval));
    }
}
