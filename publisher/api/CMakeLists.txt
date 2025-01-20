# Add source files in the models directory
set(API_SRC stock_api.cpp)

# Create a library for the models
add_library(api_lib ${API_SRC})

# Optionally include this directory for the target
target_include_directories(api_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Link the nlohmann-json library to the api_lib target
find_package(nlohmann_json REQUIRED)
target_link_libraries(api_lib PUBLIC nlohmann_json::nlohmann_json)

# Link the CPR library to the api_lib target
find_package(cpr REQUIRED)
target_link_libraries(api_lib PUBLIC cpr::cpr)