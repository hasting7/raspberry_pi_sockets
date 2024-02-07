#!/bin/bash

if [[ $(cat SERVER_STATE | egrep -x '0') ]]; then
	./web || echo 1 > SERVER_STATE

else 
	echo state is 0
fi