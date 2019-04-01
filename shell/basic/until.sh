#!/bin/sh

if [ $# != 2 ]
then
	LOOP=3
else
	LOOP=$2
fi

until [ $LOOP -le 0 ]
do
	if [ $# -ge 1 ]
	then
		>$1$LOOP
	else
		>file$LOOP
	fi
	LOOP=`expr $LOOP - 1`
done
