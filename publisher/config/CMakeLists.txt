# Add source files in the config directory
set(CONFIG_SRC config.cpp)

# Create a library for the config
add_library(config_lib ${CONFIG_SRC})

# Optionally include this directory for the target
target_include_directories(config_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Link the nlohmann-json library to the config_lib target
find_package(nlohmann_json REQUIRED)
target_link_libraries(config_lib PUBLIC nlohmann_json::nlohmann_json)
