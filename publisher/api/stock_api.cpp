#include "stock_api.h"

StockAPI::StockAPI(const std::string &apiKey)
    : apiKey(apiKey)
{
}

Stock StockAPI::getQuote(const std::string &symbol) const
{
    std::string url = "https://www.alphavantage.co/query?function=GLOBAL_QUOTE&symbol=" + symbol + "&apikey=" + apiKey;
    // Perform HTTP GET request to the URL
    auto response = cpr::Get(cpr::Url{url});

    // Parse the JSON response
    auto jsonResponse = nlohmann::json::parse(response.text);

    try
    {
        // Extract the relevant fields from the JSON response
        auto globalQuote = jsonResponse["Global Quote"];
        if (globalQuote.empty())
        {
            std::cerr << "request limit reached" << std::endl;
            return Stock(symbol, 0.0);
        }
        std::string price = globalQuote["05. price"];
        std::string volume = globalQuote["06. volume"];

        return Stock(symbol, std::stod(price));
    }
    catch (const nlohmann::json::exception &e)
    {
        std::cerr << "request limit reached" << std::endl;
        return Stock(symbol, 0.0);
    }

    return Stock(symbol, 0.0);
};