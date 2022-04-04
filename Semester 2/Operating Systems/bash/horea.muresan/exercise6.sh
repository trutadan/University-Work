#!/bin/bash

#Write a bash script that sorts the file given as command line arguments
#in ascending order according to their file size in bytes.

if [[ $# -lt 1 ]]; then
	echo Not enough arguments provided.
	exit 1
fi

for file in $@; do
	if test -f $file; then
		du -b $file
	fi
done | sort -n
