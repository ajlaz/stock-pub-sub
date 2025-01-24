# Add source files in the tcp directory
set(TCP_SRC tcp_subscriber.cpp)

# Create a library for the tcp
add_library(tcp_lib ${TCP_SRC})

# Optionally include this directory for the target
target_include_directories(tcp_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
