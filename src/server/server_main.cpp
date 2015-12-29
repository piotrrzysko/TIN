/**
 * AdvertCast
 *
 * Piotr Rżysko
 * 27.12.2015
 */

#include "UDPServer.hpp"
#include "TCPServer.hpp"

int main(int argc, char** argv)
{
    UDPServer server("224.0.0.1", "10.1.1.1", "8888");
    std::list<VideoFile> filesToSend;
    filesToSend.push_back(VideoFile(1000, "./files/test02.pdf"));
    filesToSend.push_back(VideoFile(100, "./files/test01.txt"));
    server.addFiles(filesToSend);
    server.addFileToQueue(1);
    server.addFileToQueue(2);
    server.start();


   // TCPServer tcpServer(NULL, "5555");
   // tcpServer.start();
}
