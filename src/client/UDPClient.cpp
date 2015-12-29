/**
 * AdvertCast
 *
 * Piotr Rżysko
 * 27.12.2015
 */

#include "UDPClient.hpp"

UDPClient::UDPClient(const char *multicastAddr, const char *port)
{
    if (initClient(multicastAddr, port))
    {
        logger::info << "Klient UDP zostal uruchomiony.\n";
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
        if (recvfrom(sockfd, buffer, sizeof(buffer), 0, NULL, 0) == -1)
        {
            // TODO: obsluzyc
        } else
        {
            uint fileId, number;
            std::string data;
            bool isLast = false, wrongDatagram = false;

            if (!datagramParser.matchMiddle(buffer, fileId, number, data))
            {
                if (!datagramParser.matchBegin(buffer, fileId, number, data))
                {
                    if (datagramParser.matchEnd(buffer, fileId, number, data))
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
            } else
            {
                logger::error << "Wrong datagram.\n";
            }
        }
    }

}

bool UDPClient::initClient(const char *multicastAddr, const char *port)
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
