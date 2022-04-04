#!/bin/bash

#Write a bash script that calculates the sum of the sizes (in bytes) of all regular files in a folder
#given as a parameter(use test to check if the folder exists and if a given file is a regular file).

if ! [ $# -eq 1 ]; then
	echo Only one argument must  be provided.
	exit 1
fi

if test -d $1; then
	sum_of_sizes=0

	for file in $(ls $1);do
		bytes=$(du -b $1/$file | awk '{print $1}')
		sum_of_sizes=$(($sum_of_sizes+$bytes))
	done
	
	echo $sum_of_sizes bytes
else
	echo The argument provided is not a directory.
	exit 1
fi
