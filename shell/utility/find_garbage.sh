#!/bin/bash

if [ $# -eq 0 ]
then
	echo "Usage: find_garbage PATH"
	exit
fi

C_SRC=`find $1 -name "*.c"`

for file in $C_SRC
do
	a=`grep 'main' $file -H`
	if [ ${#a} -eq 0 ]
	then
		echo $file
	fi
done

