/**
 * AdvertCast
 *
 * Piotr Rżysko
 * 30.12.2015
 */

#include "ServerController.hpp"

ServerController::ServerController() : tcpServer(nullptr), udpServer(nullptr)
{}

ServerController::~ServerController()
{
    if (tcpServer != nullptr)
        delete tcpServer;
    if (udpServer != nullptr)
        delete udpServer;
}

void ServerController::setFilesToSend(std::list<VideoFile> filesToSend)
{
    this->filesToSend = filesToSend;
}

void ServerController::setMulticastAddr(std::string multicastAddr)
{
    this->multicastAddr = multicastAddr;
}

void ServerController::setMulticastInterface(std::string multicastInterface)
{
    this->multicastInterface = multicastInterface;
}

void ServerController::setUdpPort(std::string udpPort)
{
    this->udpPort = udpPort;
}

void ServerController::setTcpPort(std::string tcpPort)
{
    this->tcpPort = tcpPort;
}

void ServerController::start()
{
    std::thread tcpServerThread(&ServerController::startTcpServer, this);
    std::thread udpServerThread(&ServerController::startUdpServer, this);
    tcpServerThread.join();
    udpServerThread.join();
}

void ServerController::startUdpServer()
{
    udpServer = new UDPServer(multicastAddr, multicastInterface, udpPort, this);
    udpServer->addFiles(filesToSend);
    udpServer->start();
}

void ServerController::startTcpServer()
{
    tcpServer = new TCPServer(tcpPort, this);
    tcpServer->start();
}

void ServerController::addFileToQueue(uint fileId)
{
    udpServer->addFileToQueue(fileId);
}

std::string ServerController::getUdpPort()
{
    return udpPort;
}

std::string ServerController::getsetMulticastAddr()
{
    return multicastAddr;
}
