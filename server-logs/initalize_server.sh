#!/bin/bash

# 1 -> path

cd $1
log_dir="server-logs"

if [[ $(cat "$log_dir/state.out" | egrep -x '0') ]]; then
	./web > "$log_dir/setup.out" 2> "$log_dir/error.out"
	if [ ! -z $? ]; then
		echo 1 > "$log_dir/state.out"
	fi

else 
	echo server already running or error check error.out >> "$log_dir/setup.out"
fi