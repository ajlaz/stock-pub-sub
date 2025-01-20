#include "stock.h"

Stock::Stock(const std::string &symbol, double price)
    : symbol(symbol), price(price)
{
}

std::string Stock::getSymbol() const
{
    return symbol;
}

double Stock::getPrice() const
{
    return price;
}

std::string Stock::toString() const
{
    return symbol + " - $" + std::to_string(price);
}