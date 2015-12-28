/**
 * AdvertCast
 *
 * Piotr Rżysko
 * 27.12.2015
 */

#ifndef ADVERTCAST_UDPCLIENT_HPP
#define ADVERTCAST_UDPCLIENT_HPP

#include "../common/MulticastUtils.hpp"

class UDPClient {
public:
    UDPClient(const char *multicastAddr, const char *port);
    void receive();
private:
    int sockfd;

    bool initClient(const char *multicastAddr, const char *port);
};


#endif //ADVERTCAST_UDPCLIENT_HPP
