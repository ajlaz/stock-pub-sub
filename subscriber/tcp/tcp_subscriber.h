#ifndef TCP_SUBSCRIBER_H
#define TCP_SUBSCRIBER_H

#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include "../models/stock.h"

class TCPSubscriber
{
public:
    TCPSubscriber(const std::string &address, int port);
    ~TCPSubscriber();

    bool start();
    void stop();
    void receiveStockData();

private:
    int clientSockfd;
    int port;
    std::string address;
    bool running;
    struct sockaddr_in serverAddr;
    void removeClient(int clientSockfd);
};

#endif