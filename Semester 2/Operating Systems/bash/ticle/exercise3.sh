#!/bin/bash

#Afișați primele 5 linii și ultimele 5 linii din fișierele de tip text din directorul curent; dacă un fișier are mai puțin de 10 linii, afișați fișierul complet.

if [ $# -ne 0 ]; then
        echo No arguments must be provided.
        exit 1
fi

current_dir_files=$(find . -maxdepth 1 -type f)

for file in $current_dir_files; do
        echo File $file:
        lines_count=$(wc $file | awk '{print $1}')

        if [ $lines_count -le 10 ]; then
                echo "$(cat $file)"
        else
                echo "$(cat $file | tail -n +6 | head -n -5)"
        fi

        echo
        
done
