#!/bin/bash

#Write a shell script that receives a filename followed by any number of strings as command line argumets. 
#The file will contain directory names. 
#The script will take all the strings that are a valide usernames in the current system and create a report 
#that will show all the direcoties found both in the file given 
#as the first argument and in the homedirs of each user received as argument. 
#If you don't have permissions to access a user homedir display a coresponding message at the standard output.

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
