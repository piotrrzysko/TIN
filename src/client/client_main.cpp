/**
 * AdvertCast
 *
 * Piotr Rżysko
 * 27.12.2015
 */

#include "UDPClient.hpp"
#include "TCPClient.hpp"

int main(int argc, char** argv)
{
    UDPClient client("224.0.0.1", "8888");
    client.start();

   // TCPClient tcpClient("10.1.1.1", "5555");
   // tcpClient.send();
}
