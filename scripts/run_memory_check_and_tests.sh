#!/bin/bash

# Exit on any error
set -e

# Define the path to valgrind
valgrind_executable="$(dirname "$BASH_SOURCE")/../dependencies/valgrind/vg-in-place"

# Define the path to the tests
tests_executable="$(dirname "$BASH_SOURCE")/../build/tests"

# Check if the tests file exists
if [ -x "$tests_executable" ]; then
    echo "Running tests: $tests_executable"
    # Run the tests
    $valgrind_executable $tests_executable
else
    echo "Error: Executable file not found at $tests_executable"
    exit 1
fi
