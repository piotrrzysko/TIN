//
// Created by marek on 07.01.16.
//


#include "mock.hpp"

int ACCEPT_RETURNS = 0;
void (*ACCEPT_BREAK)(void);
int LISTEN_RETURNS = 0;
void (*LISTEN_BREAK)(void);
ssize_t SENDTO_RETURNS = 0;
void (*SENDTO_BREAK)(void);

int accept (int __fd, __SOCKADDR_ARG __addr, socklen_t *__restrict __addr_len) {
    if (ACCEPT_BREAK)
        ACCEPT_BREAK();
    return ACCEPT_RETURNS;
}

int listen (int __fd, int __n) {
    if (LISTEN_BREAK)
        LISTEN_BREAK();
    return LISTEN_RETURNS;
}

ssize_t sendto (int __fd, const void *__buf, size_t __n,
                int __flags, __CONST_SOCKADDR_ARG __addr,
                socklen_t __addr_len) {
    if (SENDTO_BREAK)
        SENDTO_BREAK();
    return SENDTO_RETURNS;
}