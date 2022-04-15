#!/bin/bash

#Display a report showing the full name 
#of all the users currently connected, and 
#the number of processes belonging to each of them.

for user in $(cat who.fake | awk '{print $1}'); do
	processesCounter=$(cat ps.fake | grep -c -E "^$user")
	echo $user $processesCounter
done
