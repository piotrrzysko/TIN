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
#include <mutex>
#include <condition_variable>

#include "../common/VideoFile.hpp"
#include "../common/SocketFactory.hpp"
#include "../common/MulticastUtils.hpp"
#include "../common/consts.hpp"
#include "ServerController.hpp"

extern bool UDPLoopGuard;
extern unsigned int UDPSleep;

class ServerController;

class UDPServer {
public:
    UDPServer();
    UDPServer(std::string, std::string multicastInterface, std::string port, ServerController *parent);
    void addFiles(std::list<VideoFile> filesToSend);
    void addFileToQueue(uint fileId);
    void start();

private:
    struct sockaddr_storage addr;
    int sockfd;

    ServerController *parent;

    uint lastFileId;
    std::unordered_map<uint, VideoFile> videoFiles;
    std::priority_queue<VideoFile> filesToSendQueue;
    std::unordered_map<uint, TransmisionType> videoFilesInQueue;
    std::mutex mutex;
    std::condition_variable cond;

    bool initServer(std::string multicastAddr, std::string multicastInterface, std::string port);
    bool sendDatagram(uint datagramNumber, uint fileId, std::string type, std::string data, std::time_t timestamp);
    VideoFile getFromQueue();
};


#endif //ADVERTCAST_UDPSERVER_HPP
