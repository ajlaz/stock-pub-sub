# Add source files in the models directory
set(TCP_SRC tcp_publisher.cpp)

# Create a library for the models
add_library(tcp_lib ${TCP_SRC})

# Optionally include this directory for the target
target_include_directories(tcp_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Link the nlohmann-json library to the api_lib target
find_package(nlohmann_json REQUIRED)
target_link_libraries(tcp_lib PUBLIC nlohmann_json::nlohmann_json)
