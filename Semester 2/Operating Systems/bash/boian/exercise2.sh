#!/bin/bash

#Find recursively in a directory all ".c" files 
#having more than 500 lines. 
#Stop after finding 2 such files.

if [[ $# -ne 1 ]]; then
	echo Provide only one argument.
	exit 1
fi

count=0
files=$(find $1 -name '*.c')

for file in "$files"; do
	length=$(wc $file | awk '{print $1}')
	
	if [[ $length -gt 500 ]]; then
		echo $file
		count=$((count+1))
	fi

	if [[ $count -ge 2 ]]; then
		echo 2 files found, searching stopped...
		exit 1
	fi

done
