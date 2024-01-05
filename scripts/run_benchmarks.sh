#!/bin/bash

# Exit on any error
set -e

# Define the path to the benchmarks
executable_path="$(dirname "$BASH_SOURCE")/../build/benchmarks"

# Check if the benchmarks file exists
if [ -x "$executable_path" ]; then
    echo "Running benchmarks: $executable_path"
    # Run the benchmarks
    "$executable_path"
else
    echo "Error: Executable file not found at $executable_path"
    exit 1
fi

