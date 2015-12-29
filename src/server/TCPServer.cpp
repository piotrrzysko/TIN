/**
 * AdvertCast
 *
 * Piotr Rżysko
 * 28.12.2015
 */


#include "TCPServer.hpp"

#define MAX_LISTEN_QUEUE 128
#define BUFFER_SIZE 1024

TCPServer::TCPServer(const char *hostname, const char *port)
{
    if (initServer(hostname, port))
    {
        logger::info << "Serwer TCP zostal uruchomiony.\n";
    } else
    {
        logger::error << "Wystapil blad podczas uruchamiania serwera TCP.\n";
    }
}

void TCPServer::start()
{
    int connfd;
    socklen_t addrlen;
    struct sockaddr_storage clientaddr;
    char clienthost[NI_MAXHOST];
    char clientservice[NI_MAXSERV];

    while(true)
    {
        addrlen = sizeof(clientaddr);
        connfd = accept(listenfd, (struct sockaddr *)&clientaddr, &addrlen);

        if (connfd >= 0)
        {
            memset(clienthost, 0, sizeof(clienthost));
            memset(clientservice, 0, sizeof(clientservice));

            getnameinfo((struct sockaddr *)&clientaddr, addrlen, clienthost, sizeof(clienthost),
                        clientservice, sizeof(clientservice), NI_NUMERICHOST);

            logger::info << "Received request from host=[" << clienthost << "] port=[" << clientservice << "]\n";

            int rval;
            char buf[BUFFER_SIZE];
            do {
                memset(buf, 0, sizeof buf);
                if ((rval = read(connfd, buf, BUFFER_SIZE)) == -1)
                    logger:: error << "reading stream message\n";
                if (rval == 0)
                    logger::info << "Ending connection\n";
                else
                    logger::info << "-->" << buf << "\n";
            } while (rval != 0);

            close(connfd);
        } else
        {
            logger::error << "accept error::\n";
        }
    }
}

bool TCPServer::initServer(const char *hostname, const char *port)
{
    SocketFactory socketFactory;
    struct sockaddr_storage addr;

    memset(&addr, 0, sizeof(addr));
    listenfd = socketFactory.createSocket(hostname, port, AF_UNSPEC, SOCK_STREAM, &addr, false);
    if (listenfd == -1)
    {
        perror("createSocket error::");
        logger::error << "createSocket error::\n";
        return false;
    }

    if (listen(listenfd, MAX_LISTEN_QUEUE) == -1)
    {
        perror("listen error::");
        logger::error << "listen error::\n";
        return false;
    }
    return true;
}