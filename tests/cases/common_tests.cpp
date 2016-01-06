/**
 * AdvertCast
 *
 * Marek Bednarski
 * 04.01.2015
 */

#include "gtest/gtest.h"
#include "common/Args.hpp"
#include "common/MulticastUtils.hpp"
#include "common/Parser.hpp"
#include "common/SocketFactory.hpp"
#include "common/VideoFile.hpp"

TEST(CommonTests, TestArgsOptions) {
    char* argv[] = {
            "program", "-p", "5555", "-h", "10.1.1.1", "-i", "10.1.1.1", "-m", "224.0.0.1", "-u", "8888",
            "-t", "5555", "-f", "../files/video-files.txt"};
    Args args(15, argv);
    std::string arg;
    EXPECT_EQ(Arg::Port, args.getNext(arg));
    EXPECT_EQ("5555", arg);
    EXPECT_EQ(Arg::HostName, args.getNext(arg));
    EXPECT_EQ("10.1.1.1", arg);
    EXPECT_EQ(Arg::MulticastInterface, args.getNext(arg));
    EXPECT_EQ("10.1.1.1", arg);
    EXPECT_EQ(Arg::MulticastAddr, args.getNext(arg));
    EXPECT_EQ("224.0.0.1", arg);
    EXPECT_EQ(Arg::UdpPort, args.getNext(arg));
    EXPECT_EQ("8888", arg);
    EXPECT_EQ(Arg::TcpPort, args.getNext(arg));
    EXPECT_EQ("5555", arg);
    EXPECT_EQ(Arg::FilesList, args.getNext(arg));
    EXPECT_EQ("../files/video-files.txt", arg);
    EXPECT_TRUE(args.isEnd());
}

TEST(CommonTests, TestArgsFlags) {
    char* argv[] = {"program", "-help"};
    Args args(2, argv);
    std::string arg;
    EXPECT_EQ(Arg::Usage, args.getNext(arg));
    EXPECT_TRUE(args.isEnd());
}

TEST(CommonTests, TestArgsFlagAndOption) {
    char* argv[] = {"program", "-help", "-p", "5555"};
    Args args(4, argv);
    std::string arg;
    EXPECT_EQ(Arg::Usage, args.getNext(arg));
    EXPECT_EQ(Arg::Port, args.getNext(arg));
    EXPECT_EQ("5555", arg);
    EXPECT_TRUE(args.isEnd());
}

TEST(CommonTests, TestArgsUndefinedArg) {
    char* argv[] = {"program", "-fake", "fake", "5fake"};
    Args args(4, argv);
    std::string arg;
    EXPECT_EQ(Arg::Undefined, args.getNext(arg));
    EXPECT_EQ(Arg::Undefined, args.getNext(arg));
    EXPECT_EQ(Arg::Undefined, args.getNext(arg));
    EXPECT_TRUE(args.isEnd());
}

TEST(CommonTests, TestArgsGetFromFileSuccess) {
    std::ofstream tmp;
    std::list<VideoFile> vfList;
    char* argv[] = {"program", "-fake"};
    Args args(2, argv);
    tmp.open("filelist.tmp");
    tmp << "0;local/path" << std::endl
        << "1;some/path" << std::endl;
    tmp.close();
    EXPECT_TRUE(args.getFromFile("filelist.tmp", vfList));
    unlink("filelist.tmp");
    EXPECT_EQ(2, vfList.size());
    EXPECT_EQ(0, vfList.front().getTimestamp());
    EXPECT_EQ("local/path", vfList.front().getLocalPath());
    EXPECT_EQ(1, vfList.back().getTimestamp());
    EXPECT_EQ("some/path", vfList.back().getLocalPath());
}

TEST(CommonTests, TestArgsGetFromFileNoFile) {
    std::ofstream tmp;
    std::list<VideoFile> vfList;
    char* argv[] = {"program", "-fake"};
    Args args(2, argv);
    EXPECT_FALSE(args.getFromFile("filelist.tmp", vfList));
}

TEST(CommonTests, TestArgsGetFromFileWrongFile) {
    std::ofstream tmp;
    std::list<VideoFile> vfList;
    char* argv[] = {"program", "-fake"};
    Args args(2, argv);
    tmp.open("filelist.tmp");
    tmp << "" << std::endl
    << "1:some/path" << std::endl;
    tmp.close();
    EXPECT_FALSE(args.getFromFile("filelist.tmp", vfList));
    unlink("filelist.tmp");
}

TEST(CommonTests, TestVideoFile) {
    VideoFile vf(0, "local/path");
    uint id = 1;
    vf.setId(id);
    EXPECT_EQ(id, vf.getId());
    EXPECT_EQ(0, vf.getTimestamp());
    EXPECT_EQ("local/path", vf.getLocalPath());
}

TEST(CommonTests, TestVideoFileComparison) {
    VideoFile vf1(0, "local/path"), vf2(1, "some/path");
    EXPECT_TRUE(vf2 < vf1);
}

TEST(CommonTests, TestParserMatchConnect) {
    Parser parser;
    EXPECT_TRUE(parser.matchConnect(TcpMessagesTypes::Connect));
    EXPECT_FALSE(parser.matchConnect("test_string"));
}

TEST(CommonTests, TestParserMatchNAK) {
    Parser parser;
    uint clientId, fileId;
    EXPECT_TRUE(parser.matchNAK(TcpMessagesTypes::NAK + " 1 2", clientId, fileId));
    EXPECT_EQ(1, clientId);
    EXPECT_EQ(2, fileId);
    EXPECT_FALSE(parser.matchNAK("test_string", clientId, fileId));
}

TEST(CommonTests, TestParserMatchClient) {
    Parser parser;
    uint clientId;
    std::string addr, port;
    EXPECT_TRUE(parser.matchClient(TcpMessagesTypes::Client + " 1 maddr mport", clientId, addr, port));
    EXPECT_EQ(1, clientId);
    EXPECT_EQ("maddr", addr);
    EXPECT_EQ("mport", port);
    EXPECT_FALSE(parser.matchClient("test_string", clientId, addr, port));
}

TEST(CommonTests, TestParserMatchReport) {
    Parser parser;
    uint clientId, succ, err, buff;
    EXPECT_TRUE(parser.matchReport(TcpMessagesTypes::Report + " 1 2 3 4", clientId, succ, err, buff));
    EXPECT_EQ(1, clientId);
    EXPECT_EQ(2, succ);
    EXPECT_EQ(3, err);
    EXPECT_EQ(4, buff);
    EXPECT_FALSE(parser.matchReport("test_string", clientId, succ, err, buff));
}

TEST(CommonTests, TestParserMatchBegin) {
    Parser parser;
    uint fileId, number;
    ulong size;
    std::time_t stamp;
    std::string data;
    EXPECT_TRUE(parser.matchBegin(UdpMessagesTypes::Begin + " 1 2 3 4\ndata", fileId, number, stamp, size, data));
    EXPECT_EQ(1, fileId);
    EXPECT_EQ(2, number);
    EXPECT_EQ(3, stamp);
    EXPECT_EQ(4, size);
    EXPECT_EQ("data", data);
    EXPECT_FALSE(parser.matchBegin("test_string", fileId, number, stamp, size, data));
    EXPECT_FALSE(parser.matchBegin(UdpMessagesTypes::Begin + " 1 2 3 4 data", fileId, number, stamp, size, data));
}

TEST(CommonTests, TestParserMatchMiddle) {
    Parser parser;
    uint fileId, number;
    ulong size;
    std::time_t stamp;
    std::string data;
    EXPECT_TRUE(parser.matchMiddle(UdpMessagesTypes::Middle + " 1 2 3 4\ndata", fileId, number, stamp, size, data));
    EXPECT_EQ(1, fileId);
    EXPECT_EQ(2, number);
    EXPECT_EQ(3, stamp);
    EXPECT_EQ(4, size);
    EXPECT_EQ("data", data);
    EXPECT_FALSE(parser.matchMiddle("test_string", fileId, number, stamp, size, data));
    EXPECT_FALSE(parser.matchMiddle(UdpMessagesTypes::Middle + " 1 2 3 4 data", fileId, number, stamp, size, data));
}

TEST(CommonTests, TestParserMatchEnd) {
    Parser parser;
    uint fileId, number;
    ulong size;
    std::time_t stamp;
    std::string data;
    EXPECT_TRUE(parser.matchEnd(UdpMessagesTypes::End + " 1 2 3 4\ndata", fileId, number, stamp, size, data));
    EXPECT_EQ(1, fileId);
    EXPECT_EQ(2, number);
    EXPECT_EQ(3, stamp);
    EXPECT_EQ(4, size);
    EXPECT_EQ("data", data);
    EXPECT_FALSE(parser.matchEnd("test_string", fileId, number, stamp, size, data));
    EXPECT_FALSE(parser.matchEnd(UdpMessagesTypes::End + " 1 2 3 4 data", fileId, number, stamp, size, data));
}

TEST(CommonTests, TestSocketFactoryCreateSocket) {
    SocketFactory sf;
    int sockfd;
    struct sockaddr_storage addr;
    sockfd = sf.createSocket("224.0.0.1", "8888", AF_UNSPEC, SOCK_DGRAM, &addr, false);
    ASSERT_TRUE(sockfd > -1);
    close(sockfd);
    sockfd = sf.createSocket("", "5555", AF_UNSPEC, SOCK_STREAM, &addr, false);
    ASSERT_TRUE(sockfd > -1);
    close(sockfd);
    sf.createSocket("127.0.0.1", "5555", AF_UNSPEC, SOCK_STREAM, nullptr, true);
    ASSERT_TRUE(sockfd > -1);
    close(sockfd);
}

TEST(CommonTests, TestMulticastUtils) {
    MulticastUtils mu;
}