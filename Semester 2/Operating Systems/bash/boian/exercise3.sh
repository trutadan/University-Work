#!/bin/bash

#Find recursively in a directory, all the files with the extension ".log" and
#sort their lines (replace the original file with the sorted content).

if [[ $# -ne 1 ]]; then
        echo Only one argument must be provided.
        exit 1
fi

files=$(find $1 -name '*.log')

for file in $files; do
        sort $file -o $file
done
