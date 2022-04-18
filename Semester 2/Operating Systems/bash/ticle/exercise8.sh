#!/bin/bash

#Sa se scrie un fisier de comenzi care va afisa toate numele de fisiere dintr-un director dat ca parametru si din subdirectoarele sale, care au numele mai scurte de 8 caractere. Pentru acestea, daca sunt fisiere text, li se vor afisa primele 10 linii.

if [ $# -ne 1 ]; then
        echo Only one argument must be provided.
        exit 1
fi      

if ! test -d $1; then
        echo The argument must be a directory.
        exit 1
fi      

elements_found=$(find $1 2>/dev/null)
if [ $? -ne 0 ]; then
        echo Some files have been omitted omitted because you do not have the permission to access them.
fi

for file in $elements_found; do
        len=$(echo $file | sed "s/.*\///" | awk -F'.' '{ print(NF>1?length-length($NF)-1:length) }')
        
        if [[ $len -lt 8 ]]; then
                echo $file
                
                if test -f $file; then
                        echo The first 10 lines of the $file file:
                        echo $(cat $file | head -10)
                fi

                echo
        fi
done    
