#!/bin/sh


# 1: user-defined variables
count=1
echo "count = $count"

# 2: environment variables
echo $PWD
echo $HOME


# 3: command-line variables

# argument count
echo "\$#: $#"

# latest command exit status
echo "\$?: $?"

# command arguments range from $1, $2 ...
echo "\$*: $*"
echo "\$@: $@"

# current process ID
echo "\$$: $$"

# $0, $1, $2 ... $9: command arguments respectively
for arg in $*
do
	echo "\$$count: $arg"
	count=$(($count + 1))
done
