#!/bin/bash

if [ $# -ne 1 ]
then
	echo "必须提供一个需要查找的字符串"
	exit
fi

filepath=`grep "$1" . -HIrwn --exclude-dir=$1_bk | awk -F: '{print $1}' | sort | uniq`

if [ ! -e $1_bk ]
then
	mkdir $1_bk
fi


for file in $filepath
do
	dir=` echo "$file" | sed 's/\/[^/]*$//'`

	mkdir -p $1_bk/$dir
	cp $file $1_bk/$dir
done
