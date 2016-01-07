//
// Created by marek on 07.01.16.
//

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <pthread.h>

#ifndef ADVERTCAST_MOCK_H
#define ADVERTCAST_MOCK_H

extern int ACCEPT_RETURNS;
extern bool ACCEPT_BREAK;
extern int LISTEN_RETURNS;
extern bool LISTEN_BREAK;
extern ssize_t SENDTO_RETURNS;
extern bool SENDTO_BREAK;

#endif //ADVERTCAST_MOCK_H
