#!/bin/bash

n=1

# 1:
declare -i v1
v1=$n+100
echo "$v1"

# 2:
#v2=$(($n + 200))
v2=$[$n+200]
echo "$v2"

# 3:
v3=`expr $n + 300`
echo "$v3"
