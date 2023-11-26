#!/bin/bash
# This script is used to build the project.
echo "Setting compilers"
export CXX="C:\\Qt\\Tools\\mingw1120_64\\bin\\g++.exe"
export CC="C:\\Qt\\Tools\\mingw1120_64\\bin\\gcc.exe"

echo "Generating Makefile"
# Check for build dir, if not one make it.
if [ ! -d "build" ]; then
  mkdir build
fi
cd build
cmake .. -G "Ninja"

# Build the project
cmake --build .

echo "Success!"
