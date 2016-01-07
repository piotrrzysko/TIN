/**
 * AdvertCast
 *
 * Marek Bednarski
 * 04.01.2015
 */

#include <fcntl.h>
#include "gtest/gtest.h"
#include "server/ServerController.hpp"
#include "server/TCPServer.hpp"
#include "server/UDPServer.hpp"
#include "common/Args.hpp"
#include "mock.hpp"

void udpbreak(void) {
    UDPLoopGuard = false;
}

void tcpbreak(void) {
    TCPLoopGuard = false;
}

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
    UDPSleep = 0;
    server.start();
    UDPSleep = 5;
    TCPLoopGuard = true;
    UDPLoopGuard = true;
}

TEST(ServerTests, TestUDPServer) {
    ServerController sc;
    UDPServer server("224.0.0.1", "10.1.1.1", "8899", &sc);
    std::ofstream tmp1, tmp2;
    std::list<VideoFile> vfList;
    char* argv[] = {"program", "-fake"};
    Args args(2, argv);
    tmp1.open("filelist.tmp");
    tmp1 << "0;file_to_send.mp4" << std::endl;
    tmp1.close();
    tmp2.open("file_to_send.mp4");
    tmp2.seekp(1<<20);
    tmp2 << "" << std::endl;
    tmp2.close();
    args.getFromFile("filelist.tmp", vfList);
    server.addFiles(vfList);
    UDPLoopGuard = true;
    SENDTO_BREAK = &udpbreak;
    UDPSleep = 0;
    server.start();
    UDPSleep = 5;
    SENDTO_BREAK = NULL;
    UDPLoopGuard = true;
    unlink("filelist.tmp");
    unlink("file_to_send.mp4");
}

TEST(ServerTests, TestUDPServerInitWrongSocket) {
    ServerController sc;
    UDPServer server("bad", "data", "8899", &sc);
}

TEST(ServerTests, TestUDPServerInitNoMulticast) {
    ServerController sc;
    UDPServer server("10.1.1.1", "", "8891", &sc);
}

TEST(ServerTests, TestUDPServerInitNoInterface) {
    ServerController sc;
    UDPServer server("224.0.0.1", "", "8892", &sc);
}

TEST(ServerTests, TestUDPServerEmpty) {
    UDPServer server;
}

TEST(ServerTests, TestTCPServer) {
    ServerController sc;
    TCPServer server("5557", &sc);
    int fd;
    std::ofstream tmp;
    tmp.open("file.txt");
    tmp.seekp(3070);
    tmp << "" << std::endl;
    tmp.close();
    fd = open("file.txt", O_RDONLY);
    ACCEPT_RETURNS = fd;
    TCPLoopGuard = true;
    ACCEPT_BREAK = &tcpbreak;
    server.start();
    ACCEPT_BREAK = NULL;
    TCPLoopGuard = true;
    ACCEPT_RETURNS = 0;
    close(fd);
    unlink("file.txt");
}

TEST(ServerTests, TestTCPServerEmpty) {
    TCPServer tcps;
}

