/**
 * AdvertCast
 *
 * Piotr Rżysko
 * 30.12.2015
 */

#ifndef ADVERTCAST_CLIENTCONTROLLER_HPP
#define ADVERTCAST_CLIENTCONTROLLER_HPP

#include <vector>

#include "UDPClient.hpp"
#include "TCPClient.hpp"

#include "../common/consts.hpp"

class TCPClient;
class UDPClient;

class ClientController {
public:
    ClientController();
    ~ClientController();

    // UDP client
    void setMulticastAddr(std::string multicastAddr);
    void setUdpPort(std::string udpPort);

    // TCP client
    void setTcpPort(std::string tcpPort);
    void setTcpServerName(std::string tcpServerName);

    void sendNAKs(std::vector<uint> fileIds);

    void setClientId(uint clientId);

    void start();

private:
    UDPClient *udpClient;
    TCPClient *tcpClient;

    uint clientId;

    std::string multicastAddr;
    std::string udpPort;

    std::string tcpServerName;
    std::string tcpPort;

    void startTcpClient();
    void startUdpClient();
};


#endif //ADVERTCAST_CLIENTCONTROLLER_HPP
