/**
 * AdvertCast
 *
 * Piotr Rżysko
 * 29.12.2015
 */

#include "ReceivedVideoFile.hpp"

ReceivedVideoFile::ReceivedVideoFile() : lastDatagramNumber(0)
{}

bool ReceivedVideoFile::isFull()
{
    return file.size() == lastDatagramNumber;
}

void ReceivedVideoFile::addData(uint datagramNumber, std::string &data, bool isLast)
{
    if (isLast)
        lastDatagramNumber = datagramNumber;
    file[datagramNumber] = data;
}

bool ReceivedVideoFile::writeToFile(const std::string &filepath)
{
    std::fstream videoFile;
    videoFile.open(filepath, std::fstream::out);

    std::map<uint, std::string>::iterator it;
    for (it = file.begin(); it != file.end(); ++it)
    {
        videoFile << it->second;
    }
    videoFile.close();

    // TODO: obsluga bledow
    return true;
}
