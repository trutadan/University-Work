#!/bin/bash

#Write a shell script that receives a number n a word w followed by any number of files as command line arguments.
#The script will display the nth line containtng the word w from each file.

if [[ $# -lt 3 ]]; then
	echo Not enough arguments provided.
	exit 1
fi

n=$1

if ! [[ $n =~ ^[0-9]+$ ]]; then
	echo The first argument must be an integer.
	exit 1
fi

w=$2

shift 2

while [[ $# -gt 0 ]]; do
	
	file=$1

	if test -f $file; then
		echo File $file:
		line=$(cat $file | head -$n | tail -1 | grep $w)	
		
		if [[ $line =~ .+ ]]; then
			echo $line
		else
			echo $w not found on ${n}th line.
		fi

	else
		echo File $file does not exist.
	fi
	
	shift

done
