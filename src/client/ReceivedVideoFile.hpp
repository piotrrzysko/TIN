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

#include "../common/Logger.hpp"

class ReceivedVideoFile {
public:
    ReceivedVideoFile();

    bool isFull();
    void addData(uint datagramNumber, std::string &data, bool isLast);
    bool writeToFile(const std::string &filepath);

private:
    std::map<uint, std::string> file;
    uint lastDatagramNumber;
};


#endif //ADVERTCAST_RECEIVEDVIDEOFILE_HPP
