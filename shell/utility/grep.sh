#!/bin/bash

if [ $# -eq 0 ]
then
	echo "grep.sh: invalid command-line arguments"
	echo "Usage: grep.sh [FILE]"
	exit
fi

grep '^[0-9]\{3,4\}[ -]\?[0-9]\{8\}\|^([0-9]\{3,4\})[ -]\?[0-9]\{8\}' $1 --color -n
