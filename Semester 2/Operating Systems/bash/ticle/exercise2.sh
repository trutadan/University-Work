#!/bin/bash

#Afișați numele fișierelor dintr-un director dat ca parametru care conțin numere de peste 5 cifre.

if [ $# -ne 1 ]; then
        echo One argument must be provided.
        exit 1
fi

if ! test -d $1; then
        echo The argument must be a directory.
        exit 1
fi

files=$(find $1 -type f 2>/dev/null)

for file in $files; do
        if [ ! -z "$(cat $file | grep --text -E "\<[0-9]{5,}\>")" ]; then
                echo $file
        fi      
done 