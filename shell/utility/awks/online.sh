#!/bin/bash

user=`who | awk '{print $1}' | uniq`


while [ 1 ]
do
	read name

	if [ $name = "quit" ]
	then
		break
	fi

	n=0
	for u in $user
	do
		
		if [ $name = $u ]
		then
			echo "$name is online"
			n=1
			break
		fi
	done

	if [ $n -eq 0 ]
	then
		echo "$name is NOT online"
	fi
done
