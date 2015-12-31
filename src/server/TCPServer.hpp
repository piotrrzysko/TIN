/**
 * AdvertCast
 *
 * Piotr Rżysko
 * 28.12.2015
 */


#ifndef ADVERTCAST_TCPSERVER_HPP
#define ADVERTCAST_TCPSERVER_HPP

#include <vector>
#include <algorithm>

#include "../common/Logger.hpp"
#include "../common/SocketFactory.hpp"
#include "../common/Parser.hpp"
#include "ServerController.hpp"

class ServerController;

class TCPServer {
public:
    TCPServer(std::string hostname, std::string port, ServerController *parent);
    void start();
    bool hasClients();

private:
    int listenfd;
    std::string buffer;

    std::vector<int> clients;
    int lastClientId;

    ServerController *parent;
    Parser parser;

    bool initServer(std::string hostname, std::string port);
    void handleClientConnection(int connfd, char *clientservice, char *clienthost, sockaddr_storage &clientaddr);
    void handleRequest(const std::string &msg, int connfd);
    void handleConnect(int connfd);
    bool readLine(int fd, std::string* line);
};


#endif //ADVERTCAST_TCPSERVER_HPP
