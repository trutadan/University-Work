#!/bin/bash

#Write a shell script that receives as command line arguments a vaid username
#followed by a list of directories.
#The script will display all the files form the directories given as command
#line arguments that belong to the user given as the first argument.
#All input data must be validated.
#Apropriate messages will be displayed on the console in the case of invalid
#data or unexpected events.

if [[ $# -lt 2 ]]; then
        echo Not enough arguments provided.
        exit 1
fi      

username=$1

if ! cat /etc/passwd | grep -q -E "^$username:"; then
        echo The first argument provided is not a valid username.
        exit 1
fi      

shift

while [[ $# -gt 0 ]]; do

        if ! test -d $1; then
                echo Argument $1 is not a directory.

        else
                for item in $(ls $1); do
                        if test -f $item; then
                                holder=$(ls -l $item | awk '{print $3}')
                                if [[ $holder =~ $username ]]; then
                                        echo $item
                                fi
                        fi
                done
        fi

        shift
done
