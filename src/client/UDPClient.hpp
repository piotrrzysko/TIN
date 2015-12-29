/**
 * AdvertCast
 *
 * Piotr Rżysko
 * 27.12.2015
 */

#ifndef ADVERTCAST_UDPCLIENT_HPP
#define ADVERTCAST_UDPCLIENT_HPP

#include <iostream>
#include <fstream>
#include <map>

#include "../common/MulticastUtils.hpp"
#include "../common/SocketFactory.hpp"
#include "../common/consts.hpp"
#include "Parser.hpp"
#include "ReceivedVideoFile.hpp"

class UDPClient {
public:
    UDPClient(const char *multicastAddr, const char *port);
    void start();

private:
    int sockfd;

    std::map<uint, ReceivedVideoFile> videoFiles;

    bool initClient(const char *multicastAddr, const char *port);
};


#endif //ADVERTCAST_UDPCLIENT_HPP
