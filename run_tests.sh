#!/bin/bash

# Change to the directory containing the test binaries
cd bin/tests || exit

# Run all test binaries, including those in nested subfolders
find . -type f -executable | while read -r test; do
    echo "Running $test..."
    "./$test"
done
