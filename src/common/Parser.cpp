/**
 * AdvertCast
 *
 * Piotr Rżysko
 * 29.12.2015
 */

#include "Parser.hpp"

bool Parser::matchBegin(const std::string &datagram, uint &fileId, uint &number, std::time_t timestamp, ulong &size, std::string &data)
{
    return parse(UdpMessagesTypes::Begin, datagram, fileId, number, timestamp, size, data);
}

bool Parser::matchEnd(const std::string &datagram, uint &fileId, uint &number, std::time_t timestamp, ulong &size, std::string &data)
{
    return parse(UdpMessagesTypes::End, datagram, fileId, number, timestamp, size, data);
}

bool Parser::matchMiddle(const std::string &datagram, uint &fileId, uint &number, std::time_t timestamp, ulong &size, std::string &data)
{
    return parse(UdpMessagesTypes::Middle, datagram, fileId, number, timestamp, size, data);
}

bool Parser::matchNAK(const std::string &msg, uint &clientId, uint &fileId)
{
    std::string s;
    std::stringstream ss(msg);

    ss >> s;
    if (s != TcpMessagesTypes::NAK)
        return false;

    ss >> clientId >> fileId;
    return !ss.bad();
}

bool Parser::matchReport(const std::string &msg, uint &clientId, uint &succ, uint &err, uint &buff)
{
    std::string s;
    std::stringstream ss(msg);

    ss >> s;
    if (s != TcpMessagesTypes::Report)
        return false;

    ss >> clientId >> succ >> err >> buff;
    return !ss.bad();
}

bool Parser::matchConnect(const std::string &msg)
{
    std::string s;
    std::stringstream ss(msg);

    ss >> s;
    if (s != TcpMessagesTypes::Connect)
        return false;
    return true;
}

bool Parser::matchClient(const std::string &msg, uint &clientId, std::string &multicastAddr, std::string &multicastPort)
{
    std::string s;
    std::stringstream ss(msg);

    ss >> s;
    if (s != TcpMessagesTypes::Client)
        return false;

    ss >> clientId >> multicastAddr >> multicastPort;
    return !ss.bad();
}

bool Parser::parse(const std::string expectedType, const std::string &datagram, uint &fileId,
           uint &number, std::time_t timestamp, ulong &size, std::string &data)
{
    std::string s;
    std::stringstream ss(datagram);

    ss >> s;
    if (s != expectedType)
        return false;

    ss >> fileId >> number >> timestamp >> size;
    size_t newLineIndex = datagram.find("\n");
    if (newLineIndex == std::string::npos)
    {
        logger::error << "Invalid data\n";
        return false;
    }
    data = datagram.substr(newLineIndex + 1);
    return !ss.bad();
}
