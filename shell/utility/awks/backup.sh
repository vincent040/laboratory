#!/bin/bash

if [ $# -ne 1 ]
then
	echo "argument error"
	exit
fi

bk=$1_backup
echo $bk
if [ ! -d $bk ]
then
	mkdir $bk
fi



files=`grep $1 . -Hnrw --exclude-dir=.*backup | awk 'BEGIN{FS=":"} {print $1}' | uniq`

tmp=`mktemp`
for file in $files
do
	echo $file > $tmp
	bk_name=`sed 's/\//_/g; s/^\._//' $tmp`

	cp $file $bk/$bk_name
done
