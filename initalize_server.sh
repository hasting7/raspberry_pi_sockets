#!/bin/bash

if [[ $(cat $1 | egrep -x '0') ]]; then
	./web > setup.out 2> $2 || echo 1 > $1

else 
	echo state is 1
fi