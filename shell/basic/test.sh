#!/bin/bash


# a is RDONLY
declare -r a=1
echo "$a"


echo "========================"
# b will be treated as an integer
declare -i b1
read b1
b1=$b1/2
echo "b1=$b1"

read b2
b2=$b2/2
echo "b2=$b2"

read b3
b3=$(($b3/2))
echo "b3=$b3"

read b4
b4=`expr $b4 / 2`
echo "b4=$b4"


echo "========================"
# c is an array
declare -a c
c=( abc xyz 111 222 )
declare -i n=0
while [ $n -le ${#c} ]
do
	echo -e "c[$n]=${c[$n]}"
	n=$n+1
done
echo ""


echo "========================"
# v is available in f1() only
f1()
{
	declare v="abc"
}

# display function f1
declare -f f1

f2()
{
	f1
	echo $v
}

f2


echo "========================"
# display all of functions
declare -f

