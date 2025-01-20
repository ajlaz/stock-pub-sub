#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <fstream>
#include <nlohmann/json.hpp>

class Config
{
public:
    bool load(const std::string &filename);

    // accessors for the configuration data
    std::string getAPIKey() const;
    int getPollingInterval() const;

private:
    std::string alphaVantageAPIKey;
    int pollingInterval;

    bool parseJsonConfig(const std::string &filepath);
};

#endif