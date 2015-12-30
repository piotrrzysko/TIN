/**
 * AdvertCast
 *
 * Piotr Rżysko
 * 28.12.2015
 */


#ifndef ADVERTCAST_TCPCLIENT_HPP
#define ADVERTCAST_TCPCLIENT_HPP

#include <queue>
#include <mutex>

#include "../common/Logger.hpp"
#include "../common/SocketFactory.hpp"
#include "../common/consts.hpp"
#include "../common/Parser.hpp"
#include "ClientController.hpp"

class ClientController;

class TCPClient {
public:
    TCPClient(std::string hostname, std::string port, ClientController *parent);
    void start();
    void addToQueue(const std::string &msg);

private:
    int sockfd;

    uint clientId;

    mutable std::mutex mutexMsgs;
    std::queue<std::string> msgsToSend;

    ClientController *parent;
    Parser parser;

    bool initClient(std::string hostname, std::string port);
    void connectToServer();
    void send(const std::string &msg);
    std::string receive();

    std::string getFromQueue();
};


#endif //ADVERTCAST_TCPCLIENT_HPP
