#!/bin/bash

echo -n "lex src/gocompiler.l ... "
lex src/gocompiler.l
echo "Done!"

mv lex.yy.c src/lex.yy.c

echo -n "cc src/lex.yy.c -o src/gocompiler ... "
cc src/lex.yy.c -o src/gocompiler
echo "Done!"

folder_name=tests/${1}

if [ ! -d "$folder_name" ]; then
    mkdir -p "$folder_name"
fi

echo -n "./src/gocompiler -l < tests/${1}/${1}.dgo > tests/${1}/output.out ... "
./src/gocompiler -l < tests/${1}/${1}.dgo > tests/${1}/output.out
echo "Done!"

output_expected=tests/${1}/${1}.out
output_generated=tests/${1}/output.out

echo -n "diff tests/${1}/${1}.out tests/${1}/output.out ... "
diff_output=$(diff "$output_expected" "$output_generated")
echo "Done!"
echo ""
echo ""

if [ -z "$diff_output" ]; then
    echo "Test Verified: Output is 100% correct!"
else
    echo "Test Failed: Output is not correct!"
    echo "Differences found between the expected output and the generated output:\n\n"
    echo "$diff_output"
    exit 1
fi