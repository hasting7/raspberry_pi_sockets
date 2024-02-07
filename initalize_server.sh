#!/bin/bash

if [[ $(cat SERVER_STATE | egrep -x '0') ]]; then
	./web > setup.out 2> error.out || echo 1 > SERVER_STATE

else 
	echo state is 1
fi