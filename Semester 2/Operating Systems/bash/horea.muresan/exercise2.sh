#!/bin/bash

#Write a bash script that counts all the lines of code in the C files from the directory given as command-line argument,
#excluding lines that are empty or contain only spaces.

if [[ $# -lt 1 ]]; then
	echo Not enough argument provided.
	exit 1
fi

if [ ! -d "$1" ]; then
	echo Parameter given is not a folder.
	exit 1
fi

total=0
for cfile in $(ls "$1" | grep -E ".+\.c$"); do
	if test -f "$1/$cfile"; then
		nr_lines=$(cat "$1/$cfile" | grep -Ecv "^[ \t]*$")
		echo File $cfile has $nr_lines non-empty lines.
	       	total=$(($total+$nr_lines))	
	fi

done

echo Total number of lines: $total.
