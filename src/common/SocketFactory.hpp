/**
 * AdvertCast
 *
 * Piotr Rżysko
 * 28.12.2015
 */


#ifndef ADVERTCAST_SOCKETFACTORY_HPP
#define ADVERTCAST_SOCKETFACTORY_HPP

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "Logger.hpp"

class SocketFactory {
public:
    int createSocket(std::string hostname, std::string service, int family, int socktype, struct sockaddr_storage *addr,
                    bool isClient);
};


#endif //ADVERTCAST_SOCKETFACTORY_HPP
