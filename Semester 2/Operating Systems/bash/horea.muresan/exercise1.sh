#!/bin/bash

#Write a bash script that counts all the C files from a given directory and all of its subdirectories.

if [[ $# -lt 1 ]]; then
	echo Not enough arguments provided.
	exit 1
fi

find $1 -type f | grep -Eic ".+\.c$"
