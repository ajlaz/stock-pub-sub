#include <iostream>
#include "config/config.h"
#include "api/stock_api.h"
#include "models/stock.h"
#include <fstream>

int main()
{
    // Load configuration

    Config config;
    if (!config.load("../config.json"))
    {
        std::cerr << "Failed to load configuration" << std::endl;
        return 1;
    }

    // Initialize stock API
    StockAPI stockApi(config.getAPIKey());

    // Fetch stock data
    std::string stockSymbol = "AAPL";
    Stock data = stockApi.getQuote(stockSymbol);
    if (data.getSymbol() == stockSymbol)
    {
        std::cout << "Stock data for " << stockSymbol << ": " << data.toString() << std::endl;
    }
    else
    {
        std::cerr << "Failed to fetch stock data for " << stockSymbol << std::endl;
    }

    return 0;
}