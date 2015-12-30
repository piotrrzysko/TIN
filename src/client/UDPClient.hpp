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
#include <functional>
#include <chrono>
#include <thread>
#include <mutex>
#include <vector>

#include "../common/MulticastUtils.hpp"
#include "../common/SocketFactory.hpp"
#include "../common/consts.hpp"
#include "../common/Parser.hpp"
#include "ReceivedVideoFile.hpp"
#include "ClientController.hpp"

class ClientController;

class UDPClient {
public:
    UDPClient(std::string multicastAddr, std::string port, ClientController *parent);
    void start();

private:
    int sockfd;

    mutable std::mutex mutex_files;
    std::map<uint, ReceivedVideoFile> videoFiles;
    ClientController *parent;

    bool initClient(std::string multicastAddr, std::string port);
    void manageVideoFiles(uint interval);
    void startVideoFilesManage();
};


#endif //ADVERTCAST_UDPCLIENT_HPP
