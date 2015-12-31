/**
 * AdvertCast
 *
 * Piotr Rżysko
 * 27.12.2015
 */

#include "ServerController.hpp"
#include "../common/Args.hpp"

void showUsage()
{
    std::cout << "Usage: ./server -i INTERFACE -m MULTICAST_ADDR -u UDP_PORT -t TCP_PORT -f FILES_LIST" << std::endl;
}

int main(int argc, char** argv)
{
    ServerController server;
    bool portUdp = false, portTcp = false, files = false,
            interface = false, multicastAddr = false;

    if (argc != 11)
    {
        showUsage();
        return -1;
    }

    Args args(argc, argv);
    while(!args.isEnd())
    {
        std::string arg;
        switch (args.getNext(arg))
        {
            case Arg::Undefined:
            case Arg::Usage:
                showUsage();
                return EXIT_SUCCESS;

            case Arg::MulticastInterface:
                server.setMulticastInterface(arg);
                interface = true;
                break;

            case Arg::MulticastAddr:
                server.setMulticastAddr(arg);
                multicastAddr = true;
                break;

            case Arg::UdpPort:
                server.setUdpPort(arg);
                portUdp = true;
                break;

            case Arg::TcpPort:
                server.setTcpPort(arg);
                portTcp = true;
                break;

            case Arg::FilesList:
            {
                std::list<VideoFile> filesToSend;
                if (args.getFromFile(arg, filesToSend))
                {
                    server.setFilesToSend(filesToSend);
                    files = true;
                } else
                {
                    std::cout << "Wrong video list file." << std::endl;
                }
                break;
            }
            default:
                ;
        }
    }

    if (portUdp && portTcp && files && interface && multicastAddr)
    {
        server.start();
    } else
    {
        showUsage();
    }
    return EXIT_SUCCESS;
}
