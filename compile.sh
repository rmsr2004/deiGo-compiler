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
echo -n "clang src/lex.yy.c src/y.tab.c src/ast.c src/symbols.c src/codegen.c -Wall -Wno-unused-function -o src/gocompiler -g ... "
clang src/lex.yy.c src/y.tab.c src/ast.c src/symbols.c src/codegen.c -Wall -Wno-unused-function -o src/gocompiler -g
echo "Done!"

# Check if the number of arguments passed is not equal to 1
if [ "$#" -ne 1 ]; then
    # If no argument or more than one argument is passed, do not run gocompiler without arguments
    rm src/lex.yy.c src/y.tab.c src/y.tab.h src/y.output src/y.gv 
    exit 1
fi

# If the argument is '-l', run the gocompiler with the '-l' flag
if [ "$1" == "-l" ]; then
    echo "./src/gocompiler -l"
    ./src/gocompiler -l
    rm src/lex.yy.c src/y.tab.c src/y.tab.h src/y.output src/y.gv 
    exit 0
fi

# If the argument is '-t', run the gocompiler with the '-t' flag
if [ "$1" == "-t" ]; then
    echo "./src/gocompiler -t"
    ./src/gocompiler -t
    rm src/lex.yy.c src/y.tab.c src/y.tab.h src/y.output src/y.gv 
    exit 0
fi

# If the argument is '-s', run the gocompiler with the '-t' flag
if [ "$1" == "-s" ]; then
    echo "./src/gocompiler -s"
    ./src/gocompiler -s
    rm src/lex.yy.c src/y.tab.c src/y.tab.h src/y.output src/y.gv 
    exit 0
fi

# Exit if the argument is not a valid test folder
folder_name=tests/meta4/${1}
if [ ! -d "$folder_name" ]; then
    echo "File not found: $folder_name"
    rm src/lex.yy.c src/y.tab.c src/y.tab.h src/gocompiler src/y.output src/y.gv 
    exit 1
fi

# Run the gocompiler without flag to generate code, using input from the test file and saving output to a file
echo -n "./src/gocompiler < tests/meta4/${1}/${1}.dgo > tests/meta4/${1}/output.out ... "
./src/gocompiler < tests/meta4/${1}/${1}.dgo > tests/meta4/${1}/${1}.ll
echo "Done!"

echo -n "llvm-as tests/meta4/${1}/${1}.ll ... "
llvm-as tests/meta4/${1}/${1}.ll
echo "Done!"

echo "lli tests/meta4/${1}/${1}.bc > tests/meta4/${1}/output.out ... "
lli tests/meta4/${1}/${1}.bc > tests/meta4/${1}/output.out
echo "Done!"

if [[ "${1}" == *"error"* ]]; then
    sort tests/meta4/${1}/output.out -o tests/meta4/${1}/output.out
fi
echo "Done!"

# Define the paths for expected and generated output files
output_expected=tests/meta4/${1}/${1}.out
output_generated=tests/meta4/${1}/output.out

# Compare the expected output with the generated output, showing differences if any
echo -n "diff tests/meta4/${1}/${1}.out tests/meta4/${1}/output.out ... "
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

rm src/lex.yy.c src/y.tab.c src/y.tab.h src/y.output src/y.gv tests/meta4/${1}/${1}.bc