#!/bin/bash

#Sa se scrie un program shell care pentru fiecare fisier cu drepturile 755 dintr-un director (si subdirectoarele sale) 
#dat ca parametru ii schimba drepturile de acces in 744. Inainte de a schimba drepturile de acces, 
#pogramul cere confirmare din partea utilizatorului (pentru fiecare fisier in parte).

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

        if [[ $(stat $file | grep -E 'rwxr-xr-x') ]]; then
                echo "For file $file, do you want to change permissions, 'yes' or 'no'?"
                read input

                if [ $input == "yes" ]; then
                        chmod 744 $file 2>/dev/null

                        if [ $? -eq 0 ]; then
                                echo The permissions have been successfully changed.
                        else
                                echo "You don't have the rights needed to change the permission for the file $file."
                        fi
                fi
        fi
done   