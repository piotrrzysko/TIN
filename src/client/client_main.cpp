/**
 * AdvertCast
 *
 * Piotr Rżysko
 * 27.12.2015
 */

#include "ClientController.hpp"

int main(int argc, char** argv)
{
    ClientController client;
    client.setTcpPort("5555");
    client.setTcpServerName("10.1.1.1");
    client.setUdpPort("8888");
    client.setMulticastAddr("224.0.0.1");
    client.start();
}
