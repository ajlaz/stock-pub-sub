#include "config.h"

/**
 * @brief Loads the configuration data from a JSON file
 *
 * @param filename The path to the JSON file
 * @return true if the configuration was successfully loaded
 */
bool Config::load(const std::string &filename)
{
    return parseJsonConfig(filename);
}

/**
 * @brief Populates the configuration data from a JSON file
 *
 * @param filepath The path to the JSON file
 * @return true if the configuration was successfully loaded
 */
bool Config::parseJsonConfig(const std::string &filepath)
{

    nlohmann::json j;
    std::ifstream i(filepath);
    i >> j;

    alphaVantageAPIKey = j["alphaVantageAPIKey"];
    pollingInterval = j["pollingInterval"];

    if (alphaVantageAPIKey.empty() || pollingInterval == 0)
    {
        return false;
    }

    return true;
}

/**
 * @brief Returns the Alpha Vantage API key
 *
 * @return The Alpha Vantage API key
 */
std::string Config::getAPIKey() const
{
    return alphaVantageAPIKey;
}

/**
 * @brief Returns the polling interval
 *
 * @return The polling interval
 */
int Config::getPollingInterval() const
{
    return pollingInterval;
}