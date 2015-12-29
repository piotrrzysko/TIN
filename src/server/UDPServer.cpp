/**
 * AdvertCast
 *
 * Piotr Rżysko
 * 27.12.2015
 */

#include "UDPServer.hpp"

UDPServer::UDPServer(const char *multicastAddr, const char *multicastInterface, const char *port) : lastFileId(0)
{
    if (initServer(multicastAddr, multicastInterface, port))
    {
        logger::info << "Serwer UDP zostal uruchomiony.\n";
    } else
    {
        logger::error << "Wystapil blad podczas uruchamiania serwera UDP.\n";
    }
}

void UDPServer::start()
{
    // TODO: Przerobic na kolejke blokujaca
    while(!filesToSendQueue.empty())
    {
        VideoFile videofileToSend = filesToSendQueue.top();
        filesToSendQueue.pop();

        std::ifstream videoFile;
        videoFile.open(videofileToSend.getLocalPath());
        bool isBegin = true;
        uint datagramNumber = 1;
        while(!videoFile.eof())
        {
            int maxDataSize = MAX_DATAGRAM_SIZE - DATAGRAM_CUSTOM_HEADER_SIZE;
            char bytesFromFile[maxDataSize];
            memset(bytesFromFile, 0, maxDataSize);
            videoFile.read(bytesFromFile, maxDataSize);

            if (isBegin)
            {
                sendDatagram(datagramNumber, videofileToSend.getId(), DatagramTypes::Begin, bytesFromFile);
            } else
            {
                sendDatagram(datagramNumber, videofileToSend.getId(), DatagramTypes::Middle, bytesFromFile);
            }
            isBegin = false;
            datagramNumber++;
        }
        sendDatagram(datagramNumber, videofileToSend.getId(), DatagramTypes::End, "");
        videoFile.close();
    }
}

void UDPServer::addFiles(std::list<VideoFile> filesToSend)
{
    for(std::list<VideoFile>::iterator iter = filesToSend.begin(); iter != filesToSend.end(); iter++)
    {
        lastFileId++;
        videoFiles[lastFileId] = *iter;
    }
}

void UDPServer::addFileToQueue(uint fileId)
{
    if (videoFiles.find(fileId) != videoFiles.end())
    {
        VideoFile videoToQueue = videoFiles[fileId];
        videoToQueue.setId(fileId);
        filesToSendQueue.push(videoToQueue);
    }
}

bool UDPServer::initServer(const char *multicastAddr, const char *multicastInterface, const char *port)
{
    SocketFactory socketFactory;
    MulticastUtils multicastUtils;

    memset(&addr, 0, sizeof(addr));
    sockfd = socketFactory.createSocket(multicastAddr, port, AF_UNSPEC, SOCK_DGRAM, &addr, false);
    if (sockfd == -1)
    {
        perror("createSocket error::");
        logger::error << "createSocket error::\n";
        return false;
    }

    if (!multicastUtils.isMulticastAddress(&addr)<0)
    {
        logger::error << "Bledy adres multicast.\n";
        return false;
    }

    if (!multicastUtils.setMulticastInterface(sockfd, multicastInterface, &addr)<0)
    {
        logger::error << "Setting local interface error\n";
        close(sockfd);
        return false;
    }
    return true;
}

bool UDPServer::sendDatagram(uint datagramNumber, uint fileId, std::string type, std::string data)
{
    char datagram[MAX_DATAGRAM_SIZE];
    std::stringstream ss("");

    ss << type << " ";
    ss << fileId << " ";
    ss << datagramNumber << "\n";
    ss << data;

    memset(datagram, 0, MAX_DATAGRAM_SIZE);
    memcpy(datagram, ss.str().c_str(), ss.str().size());
    if (sendto(sockfd, datagram, MAX_DATAGRAM_SIZE, 0, (struct sockaddr *)&addr, sizeof(addr)) == -1)
    {
        logger::error << "sendto error\n";
        return false;
    }
    return true;
}