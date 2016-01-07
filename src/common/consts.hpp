/**
 * AdvertCast
 *
 * Piotr Rżysko
 * 27.12.2015
 */

#ifndef ADVERTCAST_CONSTS_HPP
#define ADVERTCAST_CONSTS_HPP

enum class TransmisionType {
    MULTICAST,
    UNICAST
};

namespace ArgsStr {
    const std::string Usage = "-help";
    const std::string Port = "-p";
    const std::string HostName = "-h";
    const std::string MulticastInterface = "-i";
    const std::string MulticastAddr = "-m";
    const std::string UdpPort = "-u";
    const std::string TcpPort = "-t";
    const std::string FilesList = "-f";
}

namespace UdpMessagesTypes {
    const std::string Begin = "BEGIN";
    const std::string Middle = "MIDDLE";
    const std::string End = "END";
}

namespace TcpMessagesTypes {
    const std::string NAK = "NAK";
    const std::string Report = "REPORT";
    const std::string Connect = "CONNECT";
    const std::string Client = "CLIENT";
}

#define DATAGRAM_CUSTOM_HEADER_SIZE 50
#define MAX_DATAGRAM_SIZE 65507

#define MAX_LISTEN_QUEUE 128
#define BUFFER_SIZE 1024

const uint MANAGE_VIDEO_FILES_INTERVAL = 1;
const uint MANAGE_REPORTS_INTERVAL = 10;
const uint RECONNECT_INTERVAL = 10;

const uint FILE_EXPIRATION_TIME_SEC = 2;

const std::string FILE_PREFIX = "./movie_";

#endif //ADVERTCAST_CONSTS_HPP
