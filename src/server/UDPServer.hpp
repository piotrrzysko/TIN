/**
 * AdvertCast
 *
 * Piotr Rżysko
 * 27.12.2015
 */

#ifndef ADVERTCAST_UDPSERVER_HPP
#define ADVERTCAST_UDPSERVER_HPP

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>

#include "../common/SocketFactory.hpp"
#include "../common/MulticastUtils.hpp"
#include "../common/consts.hpp"

class UDPServer {
public:
    UDPServer(const char *multicastAddr, const char *multicastInterface, const char *port);
    void send(/*const string& filePath*/);

private:
    struct sockaddr_storage addr;
    int sockfd;

    bool initServer(const char *multicastAddr, const char *multicastInterface, const char *port);
};


#endif //ADVERTCAST_UDPSERVER_HPP
