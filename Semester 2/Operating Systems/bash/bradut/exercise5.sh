#!/bin/bash

if [[ $# -lt 3 ]]; then
        echo Not enough arguments.
        exit 1
fi

f1=$1

if ! test -f $f1; then
        echo First argument is not a file.
        exit 1
fi

f2=$2

if ! test -f $f2; then
        echo Second argument is not a file.
        exit 1
fi

shift 2
echo "" > $f2
echo "" > $f1

while [[ $# -gt 0 ]]; do

        username=$1
        if ! cat /etc/passwd | awk -F: '{print $1}' | grep -q "$username"; then
                echo $username >> $f1

        else
                name=$(cat /etc/passwd | grep -E "$username:"| awk -F: '{print $5}')
                size=$(du -bs $(cat /etc/passwd | grep -E "$username:"| awk -F: '{print $6}'))
                echo $name $size
        fi



        shift
done | sort -nr > $f2