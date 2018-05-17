#!/bin/bash

cat /etc/passwd | grep -v '^#\|^$' | while read LINE
do
	USER=`awk 'BEGIN{FS=":"} {if($0~/false/) print $1}'`
	echo "$USER"
done
