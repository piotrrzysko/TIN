/**
 * AdvertCast
 *
 * Piotr Rżysko
 * 28.12.2015
 */


#include "TCPServer.hpp"

TCPServer::TCPServer(std::string hostname, std::string port, ServerController *parent) : lastClientId(0), parent(parent)
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

            std::string line;
            while(readLine(connfd, &line))
            {
                handleRequest(line, connfd);
            }
            close(connfd);
        } else
        {
            logger::error << "accept error::\n";
        }
    }
}
bool TCPServer::readLine(int fd, std::string* line)
{
    std::string::iterator pos;
    while ((pos = find(buffer.begin(), buffer.end(), '\n')) == buffer.end())
    {
        char buf [1025];
        ssize_t n = read (fd, buf, 1024);
        if (n == -1)
        {
            *line = buffer;
            buffer = "";
            return false;
        }
        buf [n] = 0;
        buffer += buf;
    }
    *line = std::string(buffer.begin(), pos);
    buffer = std::string(pos + 1, buffer.end());
    return true;
}

bool TCPServer::initServer(std::string hostname, std::string port)
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

void TCPServer::handleRequest(const std::string &msg, int connfd)
{
    uint clientId, fileId;
    std::string data;

    if (parser.matchNAK(msg, clientId, fileId))
    {
        logger::info << "Received NAK from client_id = [" << clientId << "] file_id = [" << fileId << "].\n";
        parent->addFileToQueue(fileId);
    } else if (parser.matchReport(msg, clientId, data))
    {
        logger::info << "Received REPORT from client_id = [" << clientId << "] data = [" << data << "].\n";
    } else if (parser.matchConnect(msg))
    {
        logger::info << "Received CONNECT.\n";

        handleConnect(connfd);
    } else
    {
        logger::error << "Wrong request.\n";
    }
}

void TCPServer::handleConnect(int connfd)
{
    clients.push_back(++lastClientId);

    std::stringstream ss("");
    ss << TcpMessagesTypes::Client << " " << lastClientId << "\n";

    if (write(connfd, ss.str().c_str(), ss.str().size()) == -1)
    {
        logger::error << "writing on stream socket\n";
    }
}

bool TCPServer::hasClients()
{
    return clients.size() > 0;
}
