/**
 * AdvertCast
 *
 * Piotr Rżysko
 * 27.12.2015
 */

#ifndef ADVERTCAST_CONSTS_HPP
#define ADVERTCAST_CONSTS_HPP

namespace DatagramTypes {
    const std::string Begin = "BEGIN";
    const std::string Middle = "MIDDLE";
    const std::string End = "END";
}

#define DATAGRAM_CUSTOM_HEADER_SIZE 20
#define MAX_DATAGRAM_SIZE 65507

#endif //ADVERTCAST_CONSTS_HPP
