#!/bin/bash

#Write a shell script that receives a list of arguments in the command line.
#For all arguments that are directories the script will display the fullname
#of its owner followed by the path and the size of the smallest file in its
#hierarchy. For all arguments that are files in the current directory the script
#will display the file with its lines in reverse order. All input data must be
#validated. Appropriate messages will be displayed on the console in the case of
#invalid or unexpected events.

if [ $# -lt 1 ]; then
        echo Not enough arguments provided.
        exit 1
fi

while [ $# -gt 0 ]; do

        if test -d $1; then
                owner=$(ls -la $1 | grep -E " \.$" | awk '{print $3}')
                fullname=$(cat /etc/passwd | grep -E "^$owner:" | awk -F: '{print $5}')
                file=$(find $1 | du -b | sort -n | head -1)
                echo $owner $file               

        elif test -f $1; then
                echo File $1:
                echo "$(cat $1 | tac)"

        else
                echo The argument is neither a file or a directory.

        fi

        echo
        shift
done
