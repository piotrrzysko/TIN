/**
 * AdvertCast
 *
 * Piotr Rżysko
 * 28.12.2015
 */

#include "TCPClient.hpp"


TCPClient::TCPClient(std::string hostname, std::string port, ClientController *parent) : parent(parent)
{
    if (initClient(hostname, port))
    {
        logger::info << "Klient TCP zostal uruchomiony.\n";
    } else
    {
        logger::error << "Wystapil blad podczas uruchamiania klienta TCP.\n";
    }
}

void TCPClient::start()
{
    connectToServer();
    while(true)
    {
        std::string msg = getFromQueue();
        if (msg != "")
        {
            send(msg);
        }
    }
}

bool TCPClient::initClient(std::string hostname, std::string port)
{
    SocketFactory socketFactory;
    sockfd = socketFactory.createSocket(hostname, port, AF_UNSPEC, SOCK_STREAM, nullptr, true);
    if (sockfd == -1)
    {
        perror("connect error::");
        logger::error << "connect error::\n";
        return false;
    }
    return true;
}

void TCPClient::connectToServer()
{
    logger::info << "Try connect\n";
    std::stringstream ss("");
    ss << TcpMessagesTypes::Connect << "\n";
    send(ss.str());

    std::string recMsg = receive();
    if (parser.matchClient(recMsg, clientId))
    {
        parent->setClientId(clientId);
        logger::info << "Received CLIENT from client_id = [" << clientId << "]\n";
    }
}

void TCPClient::send(const std::string &msg)
{
    if (write(sockfd, msg.c_str(), msg.size()) == -1)
    {
        logger::error << "writing on stream socket\n";
    }
}

std::string TCPClient::receive()
{
    ssize_t rval;
    char buf[BUFFER_SIZE];

    memset(buf, 0, sizeof buf);
    if ((rval = read(sockfd, buf, BUFFER_SIZE)) == -1)
    {
        logger::error << "reading stream message\n";
    }
    if (rval == 0)
    {
        logger::info << "Ending connection\n";
    }
    else
    {
        logger::info << "-->" << buf << "\n";
    }

    return buf;
}

void TCPClient::addToQueue(const std::string &msg)
{
    mutexMsgs.lock();
    msgsToSend.push(msg);
    mutexMsgs.unlock();
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
