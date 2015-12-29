/**
 * AdvertCast
 *
 * Piotr Rżysko
 * 28.12.2015
 */


#ifndef ADVERTCAST_TCPCLIENT_HPP
#define ADVERTCAST_TCPCLIENT_HPP

#include "../common/Logger.hpp"
#include "../common/SocketFactory.hpp"

class TCPClient {
public:
    TCPClient(char const*hostname, char const*port);
    void send();

private:
    int sockfd;

    bool initClient(char const*hostname, char const*port);
};


#endif //ADVERTCAST_TCPCLIENT_HPP
