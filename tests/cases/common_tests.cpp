/**
 * AdvertCast
 *
 * Marek Bednarski
 * 04.01.2015
 */

#include "gtest/gtest.h"
#include "common/Args.hpp"

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