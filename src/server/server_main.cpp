/**
 * AdvertCast
 *
 * Piotr Rżysko
 * 27.12.2015
 */

#include "UDPServer.hpp"

int main(int argc, char** argv)
{
    UDPServer server("224.0.0.1", "10.1.1.1", "8888");
    server.send();
}