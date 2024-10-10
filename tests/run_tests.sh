#!/bin/bash

current_dir="$(dirname "$0")"

for dir in "$current_dir"/*; do
    if [ -d "$dir" ]; then
        dir_name=$(basename "$dir")
        "./script.sh" "$dir_name"
    fi
done
