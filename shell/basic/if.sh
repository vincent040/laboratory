#!/bin/bash

if [ $# -eq 1 ] && [ -e $1 ]
then
	echo "yes, it does exist"
else
	echo "sorry, it's not found"
fi
