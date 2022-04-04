#!/bin/bash

#Write a bash script that receives any number of command line arguments and prints on the screen, 
#for each argument, if it is a file, a directory, a number or something else.

if [[ $# -lt 1 ]]; then
	echo Not enough arguments provided.
	exit 1
fi

while [[ $# -ge 1 ]]; do
	if test -f $1; then
		echo $1 is a file.
	elif test -d $1; then
		echo $1 is a directory.
	elif [[ $1 =~ ^[+-]?[0-9]+\.?[0-9]+$ ]]; then
		echo $1 is a number.
	else
		echo $1 is something else.
	fi

	shift
done
