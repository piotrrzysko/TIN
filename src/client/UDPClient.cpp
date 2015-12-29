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

void UDPClient::receive()
{
    char timeStr[256];
    struct sockaddr_storage clientaddr;
    socklen_t clientaddrlen = sizeof(clientaddr);

    memset(timeStr, 0, sizeof(timeStr));
    recvfrom(sockfd, timeStr, sizeof(timeStr), 0, (struct sockaddr *)&clientaddr, &clientaddrlen);
    logger::info << "Odebrano: " << timeStr;
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
