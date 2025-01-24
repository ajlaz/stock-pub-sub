#include "tcp_publisher.h"

TCPPublisher::TCPPublisher(int port, Config config, std::string &symbol)
    : port(port), running(false), serverSockfd(-1), stockApi(config.getAPIKey()), symbol(symbol), pollingInterval(config.getPollingInterval())
{
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);
}

TCPPublisher::~TCPPublisher()
{
    stop();
}

bool TCPPublisher::start()
{
    serverSockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSockfd < 0)
    {
        std::cerr << "Failed to create server socket" << std::endl;
        return false;
    }

    int reuse = 1;
    setsockopt(serverSockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

    if (bind(serverSockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
    {
        std::cerr << "Failed to bind server socket" << std::endl;
        return false;
    }

    if (listen(serverSockfd, 5) < 0)
    {
        std::cerr << "Failed to listen on server socket" << std::endl;
        return false;
    }

    running = true;

    // Wait for the first connection
    int clientSockfd;
    struct sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);
    clientSockfd = accept(serverSockfd, (struct sockaddr *)&clientAddr, &clientAddrLen);
    if (clientSockfd < 0)
    {
        std::cerr << "Failed to accept first client" << std::endl;
        running = false;
        return false;
    }

    std::cout << "Accepted first client" << std::endl;

    clients.push_back(clientSockfd);
    std::thread(&TCPPublisher::handleClient, this, clientSockfd).detach();

    // Start the stock data emit thread
    std::thread emitThread([this]()
                           {
        while (running)
        {
            Stock s = stockApi.getQuote(symbol);

            sendStockData(s);
            std::this_thread::sleep_for(std::chrono::seconds(pollingInterval));
        } });
    emitThread.detach();

    // Keep accepting new connections
    while (running)
    {
        clientSockfd = accept(serverSockfd, (struct sockaddr *)&clientAddr, &clientAddrLen);
        std::cout << "Accepted new client" << std::endl;
        if (clientSockfd < 0)
        {
            if (errno == EINTR)
                continue;
            std::cerr << "Failed to accept client" << std::endl;
            continue;
        }
        clients.push_back(clientSockfd);
        std::thread(&TCPPublisher::handleClient, this, clientSockfd).detach();
    }

    return true;
}

void TCPPublisher::stop()
{
    running = false;
    if (serverSockfd >= 0)
    {
        close(serverSockfd);
        serverSockfd = -1;
    }
}

void TCPPublisher::handleClient(int clientSockfd)
{
    // Keep the client open until stopped
    while (running)
        std::this_thread::sleep_for(std::chrono::seconds(1));
    removeClient(clientSockfd);
}

void TCPPublisher::sendStockData(const Stock &stock)
{
    std::string data = stock.toString();
    for (int sockfd : clients)
    {
        send(sockfd, data.c_str(), data.size(), 0);
    }
    std::cout << "Sent stock data: " << data << std::endl;
}

void TCPPublisher::removeClient(int clientSockfd)
{
    auto it = std::find(clients.begin(), clients.end(), clientSockfd);
    if (it != clients.end())
    {
        clients.erase(it);
        close(clientSockfd);
    }
}