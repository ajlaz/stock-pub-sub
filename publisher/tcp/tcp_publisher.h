#ifndef TCP_PUBLISHER_H
#define TCP_PUBLISHER_H

#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include "../models/stock.h"
#include "../api/stock_api.h"
#include "../config/config.h"

class TCPPublisher
{
public:
    TCPPublisher(int port, Config config, std::string &symbol);
    ~TCPPublisher();

    bool start();
    void stop();
    void sendStockData(const Stock &stock);
    void handleClient(int clientSockfd);

private:
    int serverSockfd;
    int port;
    std::vector<int> clients;
    bool running;
    struct sockaddr_in serverAddr;
    StockAPI stockApi;
    std::string &symbol;
    int pollingInterval;

    void acceptConnections();
    void removeClient(int clientSockfd);
};

#endif