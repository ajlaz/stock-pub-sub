# Add source files in the models directory
set(MODELS_SRC stock.cpp)

# Create a library for the models
add_library(models_lib ${MODELS_SRC})

# Optionally include this directory for the target
target_include_directories(models_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
