/**
 * AdvertCast
 *
 * Piotr Rżysko
 * 30.12.2015
 */


#ifndef ADVERTCAST_ARGS_HPP
#define ADVERTCAST_ARGS_HPP

#include <iostream>
#include <unordered_map>
#include <vector>
#include <list>
#include <fstream>

#include "consts.hpp"
#include "VideoFile.hpp"

enum class Arg {
    Port,
    HostName,
    Usage,
    Undefined,
    MulticastInterface,
    MulticastAddr,
    UdpPort,
    TcpPort,
    FilesList
};

static const std::unordered_map<std::string, Arg> strToArg {
    {ArgsStr::Usage, Arg::Usage},
    {ArgsStr::Port, Arg::Port},
    {ArgsStr::HostName, Arg::HostName},
    {ArgsStr::MulticastInterface, Arg::MulticastInterface},
    {ArgsStr::MulticastAddr, Arg::MulticastAddr},
    {ArgsStr::UdpPort, Arg::UdpPort},
    {ArgsStr::TcpPort, Arg::TcpPort},
    {ArgsStr::FilesList, Arg::FilesList}
};

class Args {
public:
    Args(int argc, char** argv);

    bool isEnd();
    Arg getNext(std::string &arg);
    bool getFromFile(std::string file, std::list<VideoFile> &filesToSend);

private:
    std::vector<std::string> argsVector;
    std::vector<std::string>::iterator currPos;
};


#endif //ADVERTCAST_ARGS_HPP
