/**
 * AdvertCast
 *
 * Piotr Rżysko
 * 30.12.2015
 */

#include "Args.hpp"

Args::Args(int argc, char** argv)
{
    for (int i = 1; i < argc; ++i)
    {
        std::string str = std::string(argv[i]);
        if (str.length() > 0)
        {
            argsVector.push_back(str);
        }
    }
    currPos = argsVector.begin();
}

bool Args::isEnd()
{
    return currPos == argsVector.end();
}

Arg Args::getNext(std::string &arg)
{
    std::string currentStr = *currPos;
    if (strToArg.find(currentStr) == strToArg.end())
    {
        return Arg::Undefined;
    } else
    {
        arg = *(++currPos);
        currPos++;
        return strToArg.at(currentStr);
    }
}

bool Args::getFromFile(std::string file, std::list<VideoFile> &filesToSend)
{
    std::ifstream videoListFile;
    videoListFile.open(file);
    bool error = false;

    std::string line;
    std::getline(videoListFile, line);
    while(!videoListFile.eof() && !videoListFile.bad())
    {
        std::time_t timestamp;

        size_t delimIndex = line.find(";");
        if (delimIndex != std::string::npos)
        {
            try
            {
                timestamp = std::stoi(line.substr(0, delimIndex));
            } catch(...)
            {
                error = true;
                std::cout << "It's not number!" << std::endl;
                break;
            }
            std::string videoFilePath = line.substr(delimIndex + 1);
            VideoFile v(timestamp, videoFilePath);
            filesToSend.push_back(v);
            std::getline(videoListFile, line);
        } else
        {
            error = true;
            break;
        }
    }
    videoListFile.close();

    if (videoListFile.bad() || error)
    {
        return false;
    }
    return true;
}
