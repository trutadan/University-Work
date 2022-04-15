#!/bin/bash

if [[ $# -lt 2 ]]; then
    echo Not enough arguments provided.
    exit 1
fi

filename=$1

if ! test -f $filename; then
    echo The first argument must be a file!
    exit 1
fi

shift

users=$(cat /etc/passwd | awk -F: '{print $1}')

while [[ $# -gt 0 ]]; do

    if [[ $users =~ $1 ]]; then
        homedir=$(cat /etc/passwd | grep -E $1: | awk -F: '{print $6}')
        if find $homedir > /dev/null 2> /dev/null; then
            directories=$(find $homedir)
            echo Homedir $homedir and file $filename have in common:

            while read line; do
                    echo "$directories" | grep -E "^$line$"

            done<$filename

        else
            echo Not enough rights to access $homedir.
        fi

    else
        echo User $1 not valid.
    fi

    shift
done