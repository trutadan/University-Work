#!/bin/bash

#Write a shell script that receives strings as command line arguments. 
#The first 2 arguments will represent 2 file names (f1 and f2). 
#The script will write into f2 all the arguments that are not a valid username 
#from the current system and will write in f2 all the fullnames and the size of there homedirectoryes 
#of the valid useres received as command line argumets sorted by the size of there home directories.

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
