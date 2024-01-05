#!/bin/bash

# Exit on any error
set -e

# Define the path to the tests
executable_path="$(dirname "$BASH_SOURCE")/../build/tests"

# Check if the tests file exists
if [ -x "$executable_path" ]; then
    echo "Running tests: $executable_path"
    # Run the tests
    "$executable_path"
else
    echo "Error: Executable file not found at $executable_path"
    exit 1
fi
