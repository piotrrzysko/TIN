/**
 * AdvertCast
 *
 * Piotr Rżysko
 * 27.12.2015
 */

#include "ServerController.hpp"

int main(int argc, char** argv)
{
    ServerController server;

    // TODO: do argumentow
    std::list<VideoFile> filesToSend;

    for (int t = 0; t < 2; t++)
    {
        filesToSend.push_back(VideoFile(t, "./files/test02.pdf"));
        //filesToSend.push_back(VideoFile(t, "./files/test01.txt"));
    }


    server.setFilesToSend(filesToSend);
    server.setMulticastAddr("224.0.0.1");
    server.setMulticastInterface("10.1.1.1");
    server.setUdpPort("8888");
    server.setTcpPort("5555");

    server.start();
}
