#!/bin/bash

if [ $# -gt 1 ]
then
	echo "invalid argument"
	exit
fi

# 默认计算当前目录下的文件个数
target="."

# 如果指定了某个目录，则计算指定的目录
if [ $# -eq 1 ]
then
	target=$1
fi

files=`ls $target`

count=0
for f in $files
do
	count=$(($count + 1))
done

if [ $# -eq 1 ]
then
	echo "$1下总共有$count个文件"
else
	echo "$PWD下总共有$count个文件"
fi
