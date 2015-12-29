/**
 * AdvertCast
 *
 * Piotr Rżysko
 * 29.12.2015
 */

#include "Parser.hpp"

bool Parser::matchBegin(const std::string &datagram, uint &fileId, uint &number, std::string &data)
{
    return parse(DatagramTypes::Begin, datagram, fileId, number, data);
}

bool Parser::matchEnd(const std::string &datagram, uint &fileId, uint &number, std::string &data)
{
    return parse(DatagramTypes::End, datagram, fileId, number, data);
}

bool Parser::matchMiddle(const std::string &datagram, uint &fileId, uint &number, std::string &data)
{
    return parse(DatagramTypes::Middle, datagram, fileId, number, data);
}

bool Parser::parse(const std::string expectedType, const std::string &datagram, uint &fileId,
           uint &number, std::string &data)
{
    std::string s;
    std::stringstream ss(datagram);

    ss >> s;
    if (s != expectedType)
        return false;

    ss >> fileId >> number;
    size_t index = datagram.find("\n");
    if (index == std::string::npos)
    {
        logger::error << "Invalid data\n";
        return false;
    }
    data = datagram.substr(index + 1);
    return !ss.bad();
}
