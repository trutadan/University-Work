#!/bin/bash

#Write a shell script that receives as command line arguments a word (w) followed by 2 numbers (m and n) followed by any number of files. 
#Display the files that contain on the n'th line the word w at least m times.

if [[ $# -lt 4 ]];then
	echo Not enough arguments provided.
	exit 1
fi

w=$1


int_regex='^[0-9]+$'
m=$2

if ! [[ $m =~ $int_regex ]]; then
        echo m must be an integer.
	exit 1
fi

n=$3

if ! [[ $n =~ $int_regex ]]; then
	echo n must be an integer.
        exit 1	
fi

shift
shift
shift

while [[ $# -gt 0 ]]
do

	if test -f "$1"; then
	
	line_count=1	
	while read line
	do
		if [[ $line_count -eq $n ]]
		then
			word_count=$(echo $line | awk -F"$w" '{print NF-1}')
			if [[ $word_count -ge $m ]]
			then
				echo $1	
			fi
		fi
		line_count=$(($line_count+1))
	done<$1
	
	else
		echo File $1 does not exist
	fi

	shift
done
