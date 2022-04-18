#!/bin/bash

#Sa se afiseze pentru fiecare fisier din linia de comanda linia care apare de cele mai multe ori, afisarea facandu-se in ordinea decsrescatoare a numarului de aparitii (sort, uniq, head).

if [ $# -lt 1 ]; then
        echo Not enough arguments provided.
        exit 1
fi

while [ $# -gt 0 ]; do

        if ! test -f $1; then
                echo $1 is not a file.

        else
                echo "$(cat $1 | sort | uniq -c | sort -nr | head -1)" "<- file $1" 
        fi

        shift
done | sort -nr 