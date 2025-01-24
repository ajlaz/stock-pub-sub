cmake_minimum_required(VERSION 3.10)
project(stock_subscriber)

# Require C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


# Add subdirectories
add_subdirectory(tcp)
add_subdirectory(models)


# Collect all source files from the main directory
set(SRC_FILES main.cpp)

# Add executable target
add_executable(stock_subscriber ${SRC_FILES})

# Link libraries from subdirectories
target_link_libraries(stock_subscriber PRIVATE tcp_lib models_lib)
