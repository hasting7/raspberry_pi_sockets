#!/bin/bash

# 1 -> path

cd $1

if [[ $(cat SERVER_STATE | egrep -x '0') ]]; then
	./web >> setup.out 2> error.out|| echo 1 > SERVER_STATE

else 
	echo server already running or error check error.out
fi