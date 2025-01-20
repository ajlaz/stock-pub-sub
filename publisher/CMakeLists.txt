cmake_minimum_required(VERSION 3.10)
project(stock_publisher)

# Require C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# find required libraries
find_package(nlohmann_json REQUIRED)
find_package(cpr REQUIRED)

# Add subdirectories
add_subdirectory(models)
add_subdirectory(api)
add_subdirectory(config)

# Collect all source files from the main directory
set(SRC_FILES main.cpp)

# Add executable target
add_executable(stock_publisher ${SRC_FILES})

# Link required libraries
target_link_libraries(stock_publisher PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(stock_publisher PRIVATE cpr::cpr)

# Link libraries from subdirectories
target_link_libraries(stock_publisher PRIVATE models_lib api_lib config_lib)
