#!/bin/bash

#Write a shell script that receives a number n followed by any number of files as command line arguments.
#The script will display all the words from each file with the frequency greater the n.

if [[ $# -lt 2 ]]; then
	echo Not enough arguments provided.
	exit 1
fi

n=$1

if ! [[ $n =~ ^[0-9]+$ ]]; then
	echo The first argument must be an integer.
	exit 1
fi

shift

while [[ $# -gt 0 ]]; do

	file=$1

	if test -f "$file"; then

		words=$(cat $file | tr ' ' '\n' | sort | uniq -c | sort -n -r | awk -v x=$n '{if ($1 > x) print $2}')	

		if [ -z "$words" ];then
			echo none for file $file.
		else

			echo file $file:
			for word in $words; do
				echo $word
		done

		fi
	else
		echo File $file does not exist.
	fi

	shift

done
