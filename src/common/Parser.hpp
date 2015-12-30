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

#include "consts.hpp"
#include "Logger.hpp"

class Parser {
public:
    // UDP
    bool matchBegin(const std::string &datagram, uint &fileId, uint &number, std::string &data);
    bool matchEnd(const std::string &datagram, uint &fileId, uint &number, std::string &data);
    bool matchMiddle(const std::string &datagram, uint &fileId, uint &number, std::string &data);

    // TCP
    bool matchNAK(const std::string &msg, uint &clientId, uint &fileId);
    bool matchReport(const std::string &msg, uint &clientId, std::string &data);
    bool matchConnect(const std::string &msg);
    bool matchClient(const std::string &msg, uint &clientId);

private:
    bool parse(const std::string expectedType, const std::string &datagram, uint &fileId,
               uint &number, std::string &data);
};


#endif //ADVERTCAST_PARSER_HPP
