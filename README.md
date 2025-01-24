# C++ Stock Publisher / Subscriber
## About
This is a simple demonstration of a publisher/subscriber pattern in C++ over TCP utilizing the AlphaVantage API to retrieve stock data and publish it.

## Usage
### Prerequisites
- CMake
- C++ Compiler
- AlphaVantage API Key
- cpr Library
- nlohmann/json Library

### Building
1. Clone the repository
2. Create a `config.json` file in the `publisher` directory with the following format:
```json
{
    "alphaVantageAPIKey": "API_KEY",
    "pollingInterval": 1 // in seconds
}
```
3. Run `build.sh` in the root directory
4. Run `publisher/build/stock_publisher <symbol> <port>` and `subscriber/build/stock_subscriber <hostname> <port>` in separate terminals 