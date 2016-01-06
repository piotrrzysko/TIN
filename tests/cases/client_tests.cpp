/**
 * AdvertCast
 *
 * Marek Bednarski
 * 04.01.2015
 */

#include "gtest/gtest.h"
#include "client/ClientController.hpp"
#include "client/ReceivedVideoFile.hpp"
#include "client/TCPClient.hpp"
#include "client/UDPClient.hpp"

TEST(ClientTests, TestClientController) {
    ClientController cc;
}

TEST(ClientTests, TestTCPClient) {
    TCPClient tcpc;
}

TEST(ClientTests, TestUDPClient) {
    UDPClient udpc;
}
