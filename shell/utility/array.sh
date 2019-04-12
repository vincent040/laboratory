#!/bin/bash

value="one two three four"

#a=($value)
a=(one two three four)

i=0
while [ $i -le ${#a} ]
do
	echo "a[$i]=${a[$i]}"
	i=$((i + 1))
done
