/**
 * AdvertCast
 *
 * Piotr Rżysko
 * 27.12.2015
 */

#include "UDPServer.hpp"

#define DATA "The sea is calm, the tide is full . . ."

UDPServer::UDPServer(const char *multicastAddr, const char *multicastInterface, const char *port)
{
    if (initServer(multicastAddr, multicastInterface, port))
    {
        logger::info << "Serwer UDP zostal uruchomiony.\n";
    } else
    {
        logger::error << "Wystapil blad podczas uruchamiania serwera UDP.\n";
    }
}

void UDPServer::send(/*const string& filePath*/)
{
    sendto(sockfd, DATA, sizeof(DATA), 0, (struct sockaddr *)&addr, sizeof(addr));
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

