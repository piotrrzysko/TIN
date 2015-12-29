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

#include "../common/consts.hpp"
#include "../common/Logger.hpp"

class Parser {
public:
    bool matchBegin(const std::string &datagram, uint &fileId, uint &number, std::string &data);
    bool matchEnd(const std::string &datagram, uint &fileId, uint &number, std::string &data);
    bool matchMiddle(const std::string &datagram, uint &fileId, uint &number, std::string &data);

private:
    bool parse(const std::string expectedType, const std::string &datagram, uint &fileId,
               uint &number, std::string &data);
};


#endif //ADVERTCAST_PARSER_HPP
