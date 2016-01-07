/**
 * AdvertCast
 *
 * Piotr Rżysko
 * 27.12.2015
 */

#include "MulticastUtils.hpp"

bool MulticastUtils::isMulticastAddress(struct sockaddr_storage *addr)
{
    switch (addr->ss_family)
    {
        case AF_INET:
        {
            struct sockaddr_in *addr4 = (struct sockaddr_in *)addr;
            return IN_MULTICAST(ntohl(addr4->sin_addr.s_addr));
        }
        case AF_INET6:
        {
            struct sockaddr_in6 *addr6 = (struct sockaddr_in6 *)addr;
            return IN6_IS_ADDR_MULTICAST(&addr6->sin6_addr);
        }
        default:
        {
            logger::error << "Nieobslugiwana rodzina protokolow " << addr->ss_family << "\n";
            return false;
        }
    }
}

bool MulticastUtils::joinMulticastGroup(int sockfd, struct sockaddr_storage *addr)
{
    switch (addr->ss_family)
    {
        case AF_INET:
        {
            struct ip_mreq mreq;
            mreq.imr_multiaddr.s_addr = ((struct sockaddr_in *) addr)->sin_addr.s_addr;
            mreq.imr_interface.s_addr = INADDR_ANY;

            if (setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (const void *) &mreq, sizeof(mreq)) < 0)
            {
                logger::error << "setsockopt - IP_ADD_MEMBERSHIP" << "\n";
                return false;
            }
            break;
        }
        case AF_INET6:
        {
            struct ipv6_mreq mreq6;
            memcpy(&mreq6.ipv6mr_multiaddr, &(((struct sockaddr_in6 *)addr)->sin6_addr), sizeof(struct in6_addr));
            mreq6.ipv6mr_interface = 0;

            if (setsockopt(sockfd, IPPROTO_IPV6, IPV6_ADD_MEMBERSHIP, &mreq6, sizeof(mreq6)) < 0)
            {
                logger::error << "setsockopt - IPV6_ADD_MEMBERSHIP" << "\n";
                return false;
            }
            break;
        }
        default:
        {
            logger::error << "Nieobslugiwana rodzina protokolow " << addr->ss_family << "\n";
            return false;
        }
    }
    return true;
}

bool MulticastUtils::setMulticastInterface(int sockfd, std::string multicastInterface, struct sockaddr_storage *addr)
{
    unsigned char localInterface[sizeof(struct in6_addr)];
    memset(&localInterface, 0, sizeof(localInterface));
    if (inet_pton(addr->ss_family, multicastInterface.c_str(), &localInterface) <= 0)
    {
        logger::error << "inet_pton error\n";
        return false;
    }

    int interfaceAddrLen;
    char* localInterfaceChar;
    switch (addr->ss_family)
    {
        case AF_INET:
        {
            interfaceAddrLen = sizeof(struct in_addr);
            localInterfaceChar = new char [interfaceAddrLen];
            memcpy(localInterfaceChar, localInterface, interfaceAddrLen);
            break;
        }
        case AF_INET6:
        {
            interfaceAddrLen = sizeof(struct in6_addr);
            localInterfaceChar = new char [interfaceAddrLen];
            memcpy(localInterfaceChar, localInterface, interfaceAddrLen);
            break;
        }
    }

    if(setsockopt(sockfd, IPPROTO_IP, IP_MULTICAST_IF, localInterfaceChar, interfaceAddrLen) < 0)
    {
        delete[] localInterfaceChar;
        logger::error << "Setting local interface error\n";
        return false;
    }
    delete[] localInterfaceChar;
    return true;
}
