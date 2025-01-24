#!/bin/bash

# Build the publisher

cd publisher/build
cmake ..
make

# Build the subscriber

cd ../../subscriber/build
cmake ..
make
