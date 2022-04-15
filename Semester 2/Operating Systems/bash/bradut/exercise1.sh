#!/bin/bash

#Write a shell script that counts all the C source programs of the hierarchys of all the directories received as an arguments in the command line.

if [ $# -lt 1 ]; then
	echo Not enough arguments provided.
	exit 1
fi

while [ $# -gt 0 ]; do
	if test -d $1; then
		if find $1 > /dev/null 2> /dev/null; then
			echo "$(find $1 -name '*.c' | wc -l)"
		else
			echo Access denied on $1 directory.
		fi
	else
		echo $1 is not a directory.
	fi	

	shift
done
