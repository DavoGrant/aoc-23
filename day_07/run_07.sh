#!/bin/bash

# Set the name of your C++ source file
cpp_file="day_07.cpp"

# Set the name of the compiled executable
output_name="day_07.so"

# Compile the C++ program
g++ -Wall -std=c++20 -o $output_name $cpp_file

# Check if compilation was successful
if [ $? -eq 0 ]; then
    # Run the compiled program
    ./$output_name
else
    echo "Compilation failed."
fi
