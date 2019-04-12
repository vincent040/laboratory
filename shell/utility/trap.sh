#!/bin/bash

on_exit()
{
	echo "exiting..."
}

trap on_exit EXIT
trap ":" INT

sleep 3
