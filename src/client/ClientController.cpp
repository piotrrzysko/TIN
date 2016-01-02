/**
 * AdvertCast
 *
 * Piotr Rżysko
 * 30.12.2015
 */

#include "ClientController.hpp"

ClientController::ClientController() : tcpClient(nullptr), udpClient(nullptr)
{}

ClientController::~ClientController()
{
    if (tcpClient != nullptr)
        delete tcpClient;
    if (udpClient != nullptr)
        delete udpClient;
}

void ClientController::setMulticastAddr(std::string multicastAddr)
{
    this->multicastAddr = multicastAddr;
}

void ClientController::setUdpPort(std::string udpPort)
{
    this->udpPort = udpPort;
}

void ClientController::setTcpPort(std::string tcpPort)
{
    this->tcpPort = tcpPort;
}

void ClientController::setTcpServerName(std::string tcpServerName)
{
    this->tcpServerName = tcpServerName;
}

void ClientController::start() {
    std::thread tcpClientThread(&ClientController::startTcpClient, this);
    tcpClientThread.join();
}

void ClientController::startTcpClient()
{
    tcpClient = new TCPClient(tcpServerName, tcpPort, this);
    tcpClient->start();
}

void ClientController::startUdpClient()
{
    udpClient = new UDPClient(multicastAddr, udpPort, this);
    udpClient->start();
}

void ClientController::sendNAKs(std::vector<uint> fileIds)
{
    for (std::vector<uint>::iterator it = fileIds.begin(); it != fileIds.end(); it++)
    {
        std::stringstream ss("");

        ss << TcpMessagesTypes::NAK << " " << clientId << " " << *it << "\n";
        tcpClient->addToQueue(ss.str());
    }
}

void ClientController::setClientId(uint clientId)
{
    this->clientId = clientId;
}


void ClientController::startUdpClientThread()
{
    std::thread udpClientThread(&ClientController::startUdpClient, this);
    udpClientThread.detach();
}

void ClientController::sendReport(uint succ, uint err, uint buff)
{
    std::stringstream ss("");

    ss << TcpMessagesTypes::Report << " " << clientId << " " << succ << " " << err << " " << buff << "\n";
    tcpClient->addToQueue(ss.str());
}

void ClientController::disposeUdpClientThread()
{
    if (udpClient != nullptr)
    {
        logger::info << "Try dispose UDP Client.\n";
        udpClient->dispose();
        delete udpClient;
    }
}
