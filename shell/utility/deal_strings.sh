#!/bin/sh

var="apple"

# calculate the characters in $var
n=${#var}
echo "$n"

# delete characters from left
v=${var#ap}
echo "$v"

# delete characters from left greedly
v=${var##ap}
echo "$v"

# delete characters from right
v=${var%le}
echo "$v"

# delete characters from right greedly
v=${var%%le}
echo "$v"
