#include "tcp_subscriber.h"

TCPSubscriber::TCPSubscriber(const std::string &address, int port)
    : address(address), port(port), running(false), clientSockfd(-1)
{
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    inet_pton(AF_INET, address.c_str(), &serverAddr.sin_addr);
}

TCPSubscriber::~TCPSubscriber()
{
    stop();
}

bool TCPSubscriber::start()
{
    // create the client socket
    clientSockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSockfd < 0)
    {
        std::cerr << "Failed to create client socket" << std::endl;
        return false;
    }

    // connect to the server
    if (connect(clientSockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
    {
        std::cerr << "Failed to connect to server" << std::endl;
        return false;
    }

    // start receiving stock data
    running = true;
    receiveStockData();

    return true;
}

void TCPSubscriber::stop()
{
    if (clientSockfd >= 0)
    {
        close(clientSockfd);
        clientSockfd = -1;
    }

    running = false;
}

void TCPSubscriber::removeClient(int clientSockfd)
{
    close(clientSockfd);
    clientSockfd = -1;
}

void TCPSubscriber::receiveStockData()
{
    while (running)
    {
        char buffer[1024] = {0};
        int stockData = read(clientSockfd, buffer, 1024);
        if (stockData <= 0)
        {
            std::cerr << "Failed to read stock data" << std::endl;
            break;
        }

        std::cout << "Received stock data: " << buffer << std::endl;
    }

    removeClient(clientSockfd);
}
