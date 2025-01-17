#!/bin/bash

# Name of the program to execute
program="./fix"  # Adjust the path if necessary

# Define the range for the two input numbers
first_start=0
first_end=7
second_start=0
second_end=255


# Loop through the possible combinations of the two input numbers
for (( i=first_start; i<=first_end; i++ )); do
    for (( j=second_start; j<=second_end; j++ )); do
        # Execute the program with the two numbers as stdin inputs
        if echo -e "$i\n$j\nls" | $program; then
            echo "Success with inputs: $i and $j"
            exit 0
        else
            # Check if the program crashed (exit code 139 indicates a segfault)
            exit_code=$?
            if [ $exit_code -eq 139 ]; then
                echo "Segfault occurred with inputs: $i and $j"
            else
                echo "Program exited with code $exit_code for inputs: $i and $j"
            fi
        fi
    done
done

echo "No successful combination found."
exit 1
