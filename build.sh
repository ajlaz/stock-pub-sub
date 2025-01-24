#!/bin/bash

# Create the build directories
mkdir -p publisher/build
mkdir -p subscriber/build

# Build the publisher

cd publisher/build
cmake ..
make

# Build the subscriber

cd ../../subscriber/build
cmake ..
make
