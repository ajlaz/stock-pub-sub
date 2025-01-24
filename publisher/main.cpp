#include <iostream>
#include "config/config.h"
#include "api/stock_api.h"
#include "models/stock.h"
#include "tcp/tcp_publisher.h"
#include <string>
#include <fstream>

int main(int argc, char *argv[])
{
    // Load configuration

    Config config;
    if (!config.load("../config.json"))
    {
        std::cerr << "Failed to load configuration" << std::endl;
        return 1;
    }

    if (argc < 3)
    {
        std::cerr << "Usage: " << argv[0] << " <port> <symbol>" << std::endl;
        return 1;
    }

    int port = std::stoi(argv[1]);
    std::string symbol = argv[2];
    TCPPublisher publisher(port, config, symbol);

    if (publisher.start())
    {
        std::cout << "Publisher started on port " << port << std::endl;
    }
    else
    {
        std::cerr << "Failed to start publisher on port " << port << std::endl;
        return 1;
    }

    return 0;
}