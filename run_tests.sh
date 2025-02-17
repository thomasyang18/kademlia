#!/bin/bash

# Change to the directory containing the test binaries
cd bin/tests || exit

# Run all test binaries
for test in *; do
    if [ -x "$test" ]; then
        echo "Running $test..."
        "./$test"
    fi
done
