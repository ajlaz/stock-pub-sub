#include "tcp/tcp_subscriber.h"

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cerr << "Usage: " << argv[0] << " <address> <port> " << std::endl;
        return 1;
    }

    std::string address = argv[1];
    int port = std::stoi(argv[2]);

    std::cout << "Starting subscriber at " << address << ":" << port << std::endl;
    TCPSubscriber subscriber(address, port);

    if (subscriber.start())
    {
        std::cout << "Subscriber started on " << address << ":" << port << std::endl;
    }
    else
    {
        std::cerr << "Failed to start subscriber on " << address << ":" << port << std::endl;
        return 1;
    }

    return 0;
}