#!/bin/bash

# Create an array to store the cpp files
cpp_files=()

# Loop through all cpp files in the src directory
for file in *.cpp; do
    # Add each file to the array
    cpp_files+=("$file")
done

# Compile all cpp files
g++ -std=c++17 "${cpp_files[@]}" -o program

# Check if compilation was successful
if [ $? -eq 0 ]; then
    echo "Compilation successful. Running the program..."
    # Run the compiled program
    ./program
else
    echo "Compilation failed."
fi
