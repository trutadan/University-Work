#!/bin/bash

#Write a shell script that receives an number n followed by any number of C source files as commnad line arguments.
#Display on the screen a report that shows the libreries used in each file and the top n used liraries.

if [[ $# -lt 2 ]]; then
	echo Not enough arguments provided.
	exit 1
fi

n=$1
all_libraries=()

shift

while [[ $# -gt 0 ]]
do
	if test -f "$1"; then
		if [[ $1 =~ ^.+\.c ]]; then
			libraries=$(cat $1 | grep -E "^ *# *include *[<].+[>] *$" | sed -e "s/ //g")
			echo Libraries for file $1:
			for i in ${libraries[@]}
			do
				echo $i
				all_libraries+=($i)
			done
		else
			echo $1 is not a C file.
		fi
	else
		echo $1 is not a file.
	fi

	shift
done

echo $'\n'Most common $n libraries found are:
printf '%s\n' "${all_libraries[@]}" | sort -n | uniq -c | head -$n
