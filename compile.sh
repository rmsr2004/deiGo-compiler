#!/bin/bash

set -e # Exit the script if any command returns a non-zero status (error)

# Run lex on the specified source file
echo -n "lex src/gocompiler.l ... "
lex src/gocompiler.l
echo "Done!"

# Move the generated lex.yy.c file to the src directory
mv lex.yy.c src/lex.yy.c

# Compile the lex.yy.c file into the gocompiler binary
echo -n "cc src/lex.yy.c -o src/gocompiler ... "
cc src/lex.yy.c -o src/gocompiler
echo "Done!"

# Check if the number of arguments passed is not equal to 1
if [ "$#" -ne 1 ]; then
    # If no argument or more than one argument is passed, run gocompiler without arguments
    ./src/gocompiler
    exit 1
fi

# If the argument is '-l', run the gocompiler with the '-l' flag
if [ "$1" == "-l" ]; then
    ./src/gocompiler -l
    exit 0
fi

# Exit if the argument is not a valid test folder
folder_name=tests/${1}
if [ ! -d "$folder_name" ]; then
    echo "File not found: $folder_name"
    exit 1
fi

# Run the gocompiler with the '-l' flag, using input from the test file and saving output to a file
echo -n "./src/gocompiler -l < tests/${1}/${1}.dgo > tests/${1}/output.out ... "
./src/gocompiler -l < tests/${1}/${1}.dgo > tests/${1}/output.out
echo "Done!"

# Define the paths for expected and generated output files
output_expected=tests/${1}/${1}.out
output_generated=tests/${1}/output.out

# Compare the expected output with the generated output, showing differences if any
echo -n "diff tests/${1}/${1}.out tests/${1}/output.out ... "
diff_output=$(diff --side-by-side --suppress-common-lines "$output_expected" "$output_generated" || true)
echo "Done!"
echo ""
echo ""

# If no differences are found, print success message; otherwise, print failure message with differences
if [ -z "$diff_output" ]; then
    echo "Test Verified: Output is 100% correct!"
else
    echo "Test Failed: Output is not correct!"
    echo "Differences found between the expected output and the generated output:"
    echo ""
    echo "$diff_output"
    exit 1
fi
