/**
 * AdvertCast
 *
 * Piotr Rżysko
 * 27.12.2015
 */

#include "ClientController.hpp"
#include "../common/Args.hpp"

void showUsage()
{
    std::cout << "Usage: ./client -h SERVER_NAME -p PORT" << std::endl;
}

int main(int argc, char** argv)
{
    ClientController client;
    bool port = false, serverName = false;

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

            case Arg::Port:
                client.setTcpPort(arg);
                port = true;
                break;

            case Arg::HostName:
                client.setTcpServerName(arg);
                serverName = true;
                break;
            default:
                ;
        }
    }

    if (port && serverName)
    {
        client.start();
    } else
    {
        showUsage();
    }
    return EXIT_SUCCESS;
}
