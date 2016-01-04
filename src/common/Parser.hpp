/**
 * AdvertCast
 *
 * Piotr Rżysko
 * 29.12.2015
 */

#ifndef ADVERTCAST_PARSER_HPP
#define ADVERTCAST_PARSER_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <ctime>

#include "consts.hpp"
#include "Logger.hpp"

class Parser {
public:
    // UDP
    bool matchBegin(const std::string &datagram, uint &fileId, uint &number, std::time_t timestamp, ulong &size, std::string &data);
    bool matchEnd(const std::string &datagram, uint &fileId, uint &number, std::time_t timestamp, ulong &size, std::string &data);
    bool matchMiddle(const std::string &datagram, uint &fileId, uint &number, std::time_t timestamp, ulong &size, std::string &data);

    // TCP
    bool matchNAK(const std::string &msg, uint &clientId, uint &fileId);
    bool matchReport(const std::string &msg, uint &clientId, uint &succ, uint &err, uint &buff);
    bool matchConnect(const std::string &msg);
    bool matchClient(const std::string &msg, uint &clientId, std::string &multicastAddr, std::string &multicastPort);

private:
    bool parse(const std::string expectedType, const std::string &datagram, uint &fileId,
               uint &number, std::time_t timestamp, ulong &size, std::string &data);
};


#endif //ADVERTCAST_PARSER_HPP
