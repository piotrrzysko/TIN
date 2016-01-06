/**
 * AdvertCast
 *
 * Marek Bednarski
 * 04.01.2015
 */

#include "gtest/gtest.h"
#include "server/ServerController.hpp"
#include "server/TCPServer.hpp"
#include "server/UDPServer.hpp"

TEST(ServerTests, TestServerController) {
    ServerController sc;
}

TEST(ServerTests, TestTCPServer) {
    TCPServer tcps;
}

TEST(ServerTests, TestUDPServer) {
    UDPServer udps;
}