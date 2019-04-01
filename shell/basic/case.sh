#!/bin/sh

read num

case $num in
	1)
		echo "one"
		;;
	2)
		echo "two"
		;;
	abc)
		echo "letters"
		;;
	*)
		echo "@#%$"
esac
