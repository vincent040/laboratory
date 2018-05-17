#!/bin/bash

full_path_files=`grep 'awk' . -Hnrw | awk 'BEGIN{FS=":"} {print $1}' | uniq`
bk="awks"

if [ ! -d $bk ]
then
	mkdir $bk
fi

for full_path_file in $full_path_files
do
	echo $full_path_file > files
	file_name=`awk 'BEGIN{FS="/"} {print $NF}' files`

	if [ -e "$bk/$file_name" ]
	then
		n=`ls $bk/$file_name* | wc -w`
		n=$(($n + 1))
		cp $full_path_file $bk/$file_name$n
	else
		cp $full_path_file $bk/$file_name
	fi
done
