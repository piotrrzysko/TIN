/**
 * AdvertCast
 *
 * Piotr Rżysko
 * 28.12.2015
 */


#ifndef ADVERTCAST_TCPSERVER_HPP
#define ADVERTCAST_TCPSERVER_HPP

#include "../common/Logger.hpp"
#include "../common/SocketFactory.hpp"

class TCPServer {
public:
    TCPServer(const char *hostname, const char *port);
    void start();

private:
    int listenfd;

    bool initServer(const char *hostname, const char *port);
};


#endif //ADVERTCAST_TCPSERVER_HPP
