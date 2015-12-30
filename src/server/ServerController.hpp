/**
 * AdvertCast
 *
 * Piotr Rżysko
 * 30.12.2015
 */

#ifndef ADVERTCAST_SERVERCONTROLLER_HPP
#define ADVERTCAST_SERVERCONTROLLER_HPP

#include <thread>

#include "UDPServer.hpp"
#include "TCPServer.hpp"

class UDPServer;
class TCPServer;

class ServerController {
public:
    ServerController();
    ~ServerController();

    // UDP server
    void setFilesToSend(std::list<VideoFile> filesToSend);
    void setMulticastAddr(std::string multicastAddr);
    void setMulticastInterface(std::string multicastInterface);
    void setUdpPort(std::string udpPort);

    // TCP server
    void setTcpPort(std::string tcpPort);

    void start();

    bool hasClients();
    void addFileToQueue(uint fileId);

private:
    TCPServer *tcpServer;
    UDPServer *udpServer;

    std::list<VideoFile> filesToSend;
    std::string multicastAddr;
    std::string multicastInterface;
    std::string udpPort;

    std::string tcpPort;

    void startTcpServer();
    void startUdpServer();
};

#endif //ADVERTCAST_SERVERCONTROLLER_HPP
