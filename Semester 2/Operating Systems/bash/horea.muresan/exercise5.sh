#!/bin/bash

#Write a bash script that keeps reading strings from the keyboard until the name of a readable regular file is given.

fname=""
while [ ! -f "$fname" ]; do
	read -p "Enter a string: " fname
done
