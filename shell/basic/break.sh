#!/bin/bash

count=1

while :
do
	if [ $count -gt 10 ]
	then
		break
	fi

	echo "$count"
	count=$(($count + 1))
done
