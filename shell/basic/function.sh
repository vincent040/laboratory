#!/bin/bash

check_user()
{
	if [ $1 = "quit" ]
	then
		exit
	fi

	USER=`who | grep $1 | wc -l`
	if [ $USER -eq 0 ]
	then
		return 0
	else
		return 1
	fi
}

while true
do
	echo -n "input a user name:"
	read USERNAME

	check_user $USERNAME

	if [ $? -eq 1 ]
	then
		echo "[$USERNAME] online."
	else
		echo "[$USERNAME] offline."
	fi
done
