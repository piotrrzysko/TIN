//
// Created by marek on 07.01.16.
//


#include "mock.hpp"

int ACCEPT_RETURNS = 0;
bool ACCEPT_BREAK = false;
int LISTEN_RETURNS = 0;
bool LISTEN_BREAK = false;
ssize_t SENDTO_RETURNS = 0;
bool SENDTO_BREAK = false;

int accept (int __fd, __SOCKADDR_ARG __addr, socklen_t *__restrict __addr_len) {
    if (ACCEPT_BREAK)
        pthread_exit(NULL);
    return ACCEPT_RETURNS;
}

int listen (int __fd, int __n) {
    if (LISTEN_BREAK)
        pthread_exit(NULL);
    return LISTEN_RETURNS;
}

ssize_t sendto (int __fd, const void *__buf, size_t __n,
                int __flags, __CONST_SOCKADDR_ARG __addr,
                socklen_t __addr_len) {
    if (SENDTO_BREAK)
        pthread_exit(NULL);
    return SENDTO_RETURNS;
}