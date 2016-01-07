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
#include "mock.hpp"

TEST(ServerTests, TestServerController) {
    ServerController server;
    std::list<VideoFile> vfList;
    server.setMulticastInterface("10.1.1.1");
    server.setMulticastAddr("224.0.0.1");
    server.setUdpPort("8889");
    server.setTcpPort("5556");
    server.setFilesToSend(vfList);
    EXPECT_EQ("8889", server.getUdpPort());
    EXPECT_EQ("224.0.0.1", server.getsetMulticastAddr());
    TCPLoopGuard = false;
    UDPLoopGuard = false;
    server.start();
    TCPLoopGuard = true;
    UDPLoopGuard = true;
}

TEST(ServerTests, TestTCPServer) {
    TCPServer tcps;
}

TEST(ServerTests, TestUDPServer) {
    UDPServer udps;
}