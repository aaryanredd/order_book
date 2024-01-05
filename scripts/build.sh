#!/bin/bash

# Exit on any error
set -e

# Defining the build path
build_dir="$(dirname "$BASH_SOURCE")/../build/"

# Remove the build directory if it exists
if [ -d "$build_dir" ]; then
    echo "Removing existing build directory: $build_dir"
    rm -r "$build_dir"
fi

# Create the build directory
echo "Creating build directory: $build_dir"
mkdir -p "$build_dir"

# Navigate to the build directory
echo "Changing to the build directory: $build_dir"
cd "$build_dir"

# Configure CMake with Release build type
echo "Building the code"
cmake -DCMAKE_BUILD_TYPE=Release -S .. -B .

# Build the project
make
echo "Build process complete"
