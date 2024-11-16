#!/bin/bash

set -e # Exit the script if any command returns a non-zero status (error)

# Run yacc on the specified source file
echo -n "yacc -d -v -t -g --report=all src/gocompiler.y ... "
yacc -d -v -t -g --report=all src/gocompiler.y
echo "Done!"


# Run lex on the specified source file
echo -n "lex src/gocompiler.l ... "
lex src/gocompiler.l
echo "Done!"

# Move the generated lex.yy.c, y.tab.c and y.tab.h files to the src directory
mv lex.yy.c src/lex.yy.c
mv y.tab.c src/y.tab.c
mv y.tab.h src/y.tab.h
mv y.output src/y.output
mv y.gv src/y.gv

# Compile the lex.yy.c file into the gocompiler binary
echo -n "cc src/lex.yy.c src/y.tab.c src/ast.c src/symbols.c  -Wall -Wno-unused-function -o src/gocompiler ... "
cc src/lex.yy.c src/y.tab.c src/ast.c src/symbols.c -Wall -Wno-unused-function -o src/gocompiler -g
echo "Done!"

# Check if the number of arguments passed is not equal to 1
if [ "$#" -ne 1 ]; then
    # If no argument or more than one argument is passed, do not run gocompiler without arguments
    rm src/lex.yy.c src/y.tab.c src/y.tab.h src/y.output src/y.gv 
    exit 1
fi

# If the argument is '-l', run the gocompiler with the '-l' flag
if [ "$1" == "-l" ]; then
    ./src/gocompiler -l
    rm src/lex.yy.c src/y.tab.c src/y.tab.h src/y.output src/y.gv 
    exit 0
fi

# If the argument is '-t', run the gocompiler with the '-t' flag
if [ "$1" == "-t" ]; then
    ./src/gocompiler -t
    rm src/lex.yy.c src/y.tab.c src/y.tab.h src/y.output src/y.gv 
    exit 0
fi

# Exit if the argument is not a valid test folder
folder_name=tests/meta3/${1}
if [ ! -d "$folder_name" ]; then
    echo "File not found: $folder_name"
    rm src/lex.yy.c src/y.tab.c src/y.tab.h src/gocompiler src/y.output src/y.gv 
    exit 1
fi

# Run the gocompiler with the '-s' flag, using input from the test file and saving output to a file
echo -n "./src/gocompiler -t < tests/meta3/${1}/${1}.dgo > tests/${1}/output.out ... "
./src/gocompiler -s < tests/meta3/${1}/${1}.dgo > tests/meta3/${1}/output.out
echo "Done!"

# Define the paths for expected and generated output files
output_expected=tests/meta3/${1}/${1}.out
output_generated=tests/meta3/${1}/output.out

# Compare the expected output with the generated output, showing differences if any
echo -n "diff tests/meta3/${1}/${1}.out tests/meta3/${1}/output.out ... "
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
fi

rm src/lex.yy.c src/y.tab.c src/y.tab.h src/y.output src/y.gv 