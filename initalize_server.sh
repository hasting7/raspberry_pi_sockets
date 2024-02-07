#!/bin/bash

# 1 -> path

if [[ $(cat $1/SERVER_STATE | egrep -x '0') ]]; then
	$1/web > $1/setup.out 2> $1/error.out || echo 1 > $1/SERVER_STATE

else 
	echo state is 1
fi