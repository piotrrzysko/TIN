/**
 * AdvertCast
 *
 * Piotr Rżysko
 * 29.12.2015
 */

#include "VideoFile.hpp"

VideoFile::VideoFile() : localPath(""), timestamp(0)
{}

VideoFile::VideoFile(std::time_t timestamp, std::string localPath)
        : localPath(localPath), timestamp(timestamp)
{}

std::string VideoFile::getLocalPath() const
{
    return localPath;
}

void VideoFile::setId(uint id)
{
    this->id = id;
}

uint VideoFile::getId() const
{
    return id;
}

std::time_t VideoFile::getTimestamp() const
{
    return timestamp;
}

bool operator<(const VideoFile& lhs, const VideoFile& rhs)
{
    return lhs.getTimestamp() > rhs.getTimestamp();
}
