/**
 * AdvertCast
 *
 * Piotr Rżysko
 * 29.12.2015
 */
#ifndef ADVERTCAST_RECEIVEDVIDEOFILE_HPP
#define ADVERTCAST_RECEIVEDVIDEOFILE_HPP

#include <iostream>
#include <chrono>
#include <ctime>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>

#include "../common/consts.hpp"
#include "../common/Logger.hpp"

class ReceivedVideoFile {
public:
    ReceivedVideoFile();

    bool isFull();
    void addData(uint datagramNumber, std::string &data, bool isLast, std::time_t timestamp);
    bool writeToFile(const std::string &filepath);
    bool isExpired();
    std:: time_t getTimestamp();

private:
    std::map<uint, std::string> file;
    uint lastDatagramNumber;
    std::chrono::time_point<std::chrono::system_clock> lastModification;
    std::time_t timestamp;
};


#endif //ADVERTCAST_RECEIVEDVIDEOFILE_HPP
