#ifndef STOCK_API_H
#define STOCK_API_H

#include <string>
#include <nlohmann/json.hpp>
#include <cpr/cpr.h>
#include "../models/stock.h"

class StockAPI
{
public:
    StockAPI(const std::string &apiKey);
    Stock getQuote(const std::string &symbol) const;

private:
    std::string apiKey;
};

#endif