#!/bin/bash

# check build directory
if [[ -d build ]]
then
  rm -rf build
fi

# go to build directory
mkdir build && cd build

# and create libBlink.so
cmake .. && cmake --build .
