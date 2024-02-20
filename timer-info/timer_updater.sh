#!/bin/bash

cd $1

timer="timer.duration"

if [[ $(cat $timer | egrep '^-1$' ) ]]; then
	echo timer not on
	exit 1
fi

./decrement_time "./$timer"
$updated=$?
echo UPDATED TIMER $updated
echo $updated > $timer

if [ -z $updated ]; then
	./color_change.sh 127.0.0.1 5566 0
	if [ -z $? ]; then
		echo lights turned off
		exit 0
	else
		echo error talking to server 
		exit 1
	fi
else
	echo timer incremeted down
fi