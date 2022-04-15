#!/bin/bash

#Write a shell script that receives as command line arguments files. Display on the screen the frequency of the even numbers in each of the files.

if [ $# -lt 1 ]; then
        echo "Not enough arguments."
        exit 1
fi

while [[ $# -gt 0 ]]; do
        file=$1
        if test -f $file; then
                message=$(cat $file | awk '{
                for(i=1;i<=NF;i++)
                        if ($i ~ /^[0-9]*[02468]$/)
                                freq[$i]++;
                }
                END{
                        for (elem in freq) 
                                print "Number " elem " has frequency " freq[elem]}
                                                                                ')
                echo "$message"
        else
                echo "The $1 argument is not a file"    
        fi

        shift
done
