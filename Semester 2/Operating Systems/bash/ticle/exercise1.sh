#!/bin/bash

#Calculați numărul mediu de linii din fișierele text dintr-un director dat ca parametru.

if [ $# -ne 1 ]; then
        echo Only one argument must be provided.
        exit 1
fi

if ! test -d $1; then
        echo The argument must be a directory.
        exit 1
fi

sum=0
files_counter=0

files=$(find $1 -type f 2>/dev/null)

for file in $files; do
        line_counter=$(cat $file | wc | awk '{print $2}')
        sum=$((sum+line_counter))
        ((files_counter++))
done

echo The average number of lines in a file: $((sum/files_counter))
