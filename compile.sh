
#!/bin/bash

set -e # Ends the script when an error it's found

echo -n "lex src/gocompiler.l ... "
lex src/gocompiler.l
echo "Done!"

mv lex.yy.c src/lex.yy.c

echo -n "cc src/lex.yy.c -o src/gocompiler ... "
cc src/lex.yy.c -o src/gocompiler
echo "Done!"

if [ "$#" -ne 1 ]; then
    ./src/gocompiler

    exit 1
fi

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
diff_output=$(diff --side-by-side --suppress-common-lines "$output_expected" "$output_generated" || true)
echo "Done!"
echo ""
echo ""

if [ -z "$diff_output" ]; then
    echo "Test Verified: Output is 100% correct!"
else
    echo "Test Failed: Output is not correct!"
    echo "Differences found between the expected output and the generated output:"
    echo ""
    echo "$diff_output"
    exit 1
fi
