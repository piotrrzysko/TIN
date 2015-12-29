/**
 * AdvertCast
 *
 * Piotr Rżysko
 * 29.12.2015
 */

#ifndef ADVERTCAST_VIDEOFILE_HPP
#define ADVERTCAST_VIDEOFILE_HPP

#include <iostream>
#include <chrono>
#include <ctime>

class VideoFile {
public:
    VideoFile();
    VideoFile(std::time_t timestamp, std::string localPath);

    std::string getLocalPath() const;
    std::time_t getTimestamp() const;
    uint getId() const;
    void setId(uint id);

private:
    std::string localPath;
    std::time_t timestamp;
    uint id;
};

bool operator<(const VideoFile& lhs, const VideoFile& rhs);

#endif //ADVERTCAST_VIDEOFILE_HPP
