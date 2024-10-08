#!/bin/bash

lex src/gocompiler.l

cc src/lex.yy.c -o src/gocompiler

folder_name=tests/${1}

if [ ! -d "$folder_name" ]; then
    mkdir -p "$folder_name"
fi

./src/gocompiler -l < tests/${1}/${1}.dgo > tests/${1}/${1}.out