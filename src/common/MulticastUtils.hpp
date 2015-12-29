/**
 * AdvertCast
 *
 * Piotr Rżysko
 * 27.12.2015
 */

#ifndef ADVERTCAST_MULTICASTUTILS_HPP
#define ADVERTCAST_MULTICASTUTILS_HPP

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "Logger.hpp"

class MulticastUtils {
public:
    bool isMulticastAddress(struct sockaddr_storage *addr);
    bool joinMulticastGroup(int sockfd, struct sockaddr_storage *addr);
    bool setMulticastInterface(int sockfd, const char *multicastInterface, struct sockaddr_storage *addr);
};


#endif //ADVERTCAST_MULTICASTUTILS_HPP
