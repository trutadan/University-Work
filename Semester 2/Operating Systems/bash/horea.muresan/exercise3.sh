#!/bin/bash

#Write a bash script that counts all the lines of code in the C files from the directory 
#given as command-line argument and all its subdirectories, excluding lines that are empty or contain only spaces.

if [[ $# -lt 1 ]]; then
	echo Not enough arguments provided.
	exit 1
fi

if [ ! -d "$1" ]; then
	echo Parameter given is not a folder.
	exit 1
fi 

total=0
for cfile in $(find "$1" -type f | grep -E ".+\.c$"); do
	nr_lines=$(cat $cfile | grep -cEv "^[ \t]*$")
	echo File $cfile has $nr_lines c non-empty lines.
	total=$(($total+$nr_lines))
done

echo Total number of c non-emtpy lines: $total.
