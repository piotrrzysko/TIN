/**
 * AdvertCast
 *
 * Piotr Rżysko
 * 28.12.2015
 */

#include "TCPClient.hpp"

TCPClient::TCPClient() { }

TCPClient::TCPClient(std::string hostname, std::string port, ClientController *parent)
        : hostname(hostname), port(port), isConnected(false), parent(parent)
{}

void TCPClient::start()
{
    connectToServer();
    while(true)
    {
        if(!send(getFromQueue()))
        {
            isConnected = false;
            parent->disposeUdpClientThread();
            close(sockfd);
            mutexMsgs.lock();
            std::queue<std::string> empty;
            std::swap(msgsToSend, empty);
            mutexMsgs.unlock();
            connectToServer();
        }
    }
}

bool TCPClient::initClient(std::string hostname, std::string port)
{
    SocketFactory socketFactory;
    sockfd = socketFactory.createSocket(hostname, port, AF_UNSPEC, SOCK_STREAM, nullptr, true);
    if (sockfd == -1)
    {
        return false;
    }
    signal(SIGPIPE, SIG_IGN);
    return true;
}

void TCPClient::connectToServer()
{
    while (!tryConnectToServer())
    {
        logger::error << "Error connecting to TCP server. Trying again...\n";
        std::this_thread::sleep_for (std::chrono::seconds(RECONNECT_INTERVAL));
    }
}

bool TCPClient::tryConnectToServer()
{
    logger::info << "Connecting to TCP server...\n";
    if (initClient(hostname, port))
    {
        isConnected = true;
        logger::info << "Connected to TCP server.\n";

        std::stringstream ss("");
        ss << TcpMessagesTypes::Connect << "\n";
        send(ss.str());

        std::string multiAddr;
        std::string multiPort;
        std::string recMsg = receive();
        if (parser.matchClient(recMsg, clientId, multiAddr, multiPort))
        {
            parent->setMulticastAddr(multiAddr);
            parent->setUdpPort(multiPort);
            parent->setClientId(clientId);
            parent->startUdpClientThread();
            logger::info << "Received CLIENT from client_id = [" << clientId << "]\n";
            return true;
        }
    } else
    {
        isConnected = false;
    }
    return false;
}

bool TCPClient::send(const std::string &msg)
{
    if (msg != "")
    {
        if (write(sockfd, msg.c_str(), msg.size()) == -1)
        {
            logger::error << "Error when writing on stream socket.\n";
            return false;
        }
    }
    return true;
}

std::string TCPClient::receive()
{
    char buf[BUFFER_SIZE];

    memset(buf, 0, sizeof buf);
    if (read(sockfd, buf, BUFFER_SIZE) == -1)
    {
        logger::error << "Error when reading stream message.\n";
    }
    return buf;
}

void TCPClient::addToQueue(const std::string &msg)
{
    if (isConnected)
    {
        mutexMsgs.lock();
        msgsToSend.push(msg);
        mutexMsgs.unlock();
    }
}

std::string TCPClient::getFromQueue()
{
    mutexMsgs.lock();
    std::string msg = "";
    if (!msgsToSend.empty())
    {
        msg = msgsToSend.front();
        msgsToSend.pop();
    }
    mutexMsgs.unlock();
    return msg;
}
