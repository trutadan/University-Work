#!/bin/bash

#Write a shell script that receives a list of strings as a command line arguments.
#For all the strings received as a commnad line arguments that are valid
#usernames in the curent system the script will display the homedir and the
#fullname of the user.
#The script will also display the sum of all arguments received that are numbers.
#All input data must be validated.
#Apropriate messages will be displayed on the console in the case of invalid
#data or unexpected events.

if [[ $# -lt 1 ]]; then
        echo Not enough arguments provided.
        exit 1
fi

sum=0

while [[ $# -gt 0 ]]; do
        user=$1

        if [[ $1 =~ ^[-+]?[0-9]+$ ]]; then
                sum=$((sum+$1))

        elif cat /etc/passwd | grep -q -E "^$user:"; then
                echo $(cat /etc/passwd | grep -E "^$user:" | awk -F: '{print $5}' | cut -d ',' -f 1) $(cat /etc/passwd | grep -E "^$user:" | awk -F: '{print $(NF-1)}')
        
        else
                echo $1 is neither a number or an user.

        fi

        shift
done    

echo The sum of the numbers passed as arguments is $sum.
