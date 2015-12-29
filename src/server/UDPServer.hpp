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
#include <unordered_map>
#include <list>
#include <queue>
#include <iostream>
#include <fstream>
#include <sstream>

#include "VideoFile.hpp"
#include "../common/SocketFactory.hpp"
#include "../common/MulticastUtils.hpp"
#include "../common/consts.hpp"

class UDPServer {
public:
    UDPServer(const char *multicastAddr, const char *multicastInterface, const char *port);
    void addFiles(std::list<VideoFile> filesToSend);
    void addFileToQueue(uint fileId);
    void start();

private:
    struct sockaddr_storage addr;
    int sockfd;

    uint lastFileId;
    std::unordered_map<uint, VideoFile> videoFiles;
    std::priority_queue<VideoFile> filesToSendQueue;

    bool initServer(const char *multicastAddr, const char *multicastInterface, const char *port);
    bool sendDatagram(uint datagramNumber, uint fileId, std::string type, std::string data);
};


#endif //ADVERTCAST_UDPSERVER_HPP
