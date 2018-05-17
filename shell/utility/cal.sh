#!/bin/bash

declare -i a=100
a=$a/2
echo $a

b=100
b=$(($b/2))
echo $b

c=100
c=`expr $c / 2`
echo $c
