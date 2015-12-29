/**
 * AdvertCast
 *
 * Piotr Rżysko
 * 28.12.2015
 */

#include "SocketFactory.hpp"

int SocketFactory::createSocket(const char *hostname, const char *service, int family, int socktype,
                                struct sockaddr_storage *addr, bool isClient)
{
    struct addrinfo hints, *addrCandidates, *addrCandidatesHead;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_flags = AI_PASSIVE;
    hints.ai_family = family;
    hints.ai_socktype = socktype;

    if (int error = getaddrinfo(hostname, service, &hints, &addrCandidates) < 0)
    {
        logger::error << "getaddrinfo error:: " << gai_strerror(error) << "\n";
        return -1;
    }

    int sockfd = -1;
    addrCandidatesHead = addrCandidates;
    while (addrCandidates)
    {
        sockfd = socket(addrCandidates->ai_family, addrCandidates->ai_socktype, addrCandidates->ai_protocol);
        if (sockfd > -1)
        {
            int bindConnectResult;
            if (isClient)
            {
                bindConnectResult = connect(sockfd, addrCandidates->ai_addr, addrCandidates->ai_addrlen);
            } else
            {
                bindConnectResult = bind(sockfd, addrCandidates->ai_addr, addrCandidates->ai_addrlen);
            }
            if (bindConnectResult == 0)
            {
                if (addr != nullptr)
                    memcpy(addr, addrCandidates->ai_addr, sizeof(*addr));
                break;
            }
            close(sockfd);
            sockfd = -1;
        }
        addrCandidates = addrCandidates->ai_next;
    }

    freeaddrinfo(addrCandidatesHead);
    return sockfd;
}