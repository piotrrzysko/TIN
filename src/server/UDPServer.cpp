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
    MulticastUtils utils;

    memset(&addr, 0, sizeof(addr));
    if (!utils.getAddress(multicastAddr, port, PF_UNSPEC, SOCK_DGRAM, &addr))
    {
        return false;
    }

    if (!utils.isMulticastAddress(&addr)<0)
    {
        logger::error << "Bledy adres multicast.\n";
        return false;
    }

    sockfd = socket(addr.ss_family, SOCK_DGRAM, 0);
    if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        logger::error << "bind error::\n";
        close(sockfd);
        return false;
    }

    if (!utils.setMulticastInterface(sockfd, multicastInterface, &addr)<0)
    {
        logger::error << "Setting local interface error\n";
        close(sockfd);
        return false;
    }
    return true;
}

