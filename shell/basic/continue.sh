#!/bin/bash

mod=`lsmod | awk '{print $1}'`

for m in $mod
do
	if [ $1 != $m ]
	then
		continue
	fi

	echo "$1 is INSTALLED"
	exit
done

echo "$1 is NOT installed"
