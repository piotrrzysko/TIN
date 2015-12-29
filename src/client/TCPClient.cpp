/**
 * AdvertCast
 *
 * Piotr Rżysko
 * 28.12.2015
 */


#include "TCPClient.hpp"

#define DATA "Half a league, half a league . . ."

TCPClient::TCPClient(const char *hostname, const char *port)
{
    if (initClient(hostname, port))
    {
        logger::info << "Klient TCP zostal uruchomiony.\n";
    } else
    {
        logger::error << "Wystapil blad podczas uruchamiania klienta TCP.\n";
    }
}

void TCPClient::send()
{
    if (write(sockfd, DATA, sizeof DATA) == -1)
    {
        logger::error << "writing on stream socket\n";
    }
    close(sockfd);
}

bool TCPClient::initClient(const char *hostname, const char *port)
{
    SocketFactory socketFactory;
    sockfd = socketFactory.createSocket(hostname, port, AF_UNSPEC, SOCK_STREAM, nullptr, true);
    if (sockfd == -1)
    {
        perror("connect error::");
        logger::error << "connect error::\n";
        return false;
    }
    return true;
}