#!/bin/sh

if test $# -eq 2
then
	LOOP=$2
else
	LOOP=3
fi

while [ $LOOP -gt 0 ]
#while test $LOOP -gt 0
do
	if test $# -ge 1
	then
		>$1$LOOP
	else
		>file$LOOP
	fi
	LOOP=`expr $LOOP - 1`
done
