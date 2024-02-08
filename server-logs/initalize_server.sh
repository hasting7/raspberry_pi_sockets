#!/bin/bash

# 1 -> path

cd $1
log_dir="server-logs"
web_dir="web-src"

for file in "state.out" "setup.out"; do
	if [ ! -e "$log_dir/$file" ]; then
		echo "$file DNE" >> "$log_dir/error.out" 
		exit 1
	fi
done
for file in "header" "main.html"; do
	if [ ! -e "$web_dir/$file" ]; then
		echo "$file DNE" >> "$log_dir/error.out" 
		exit 1
	fi
done



if [[ $(cat "$log_dir/state.out" | egrep -x '0') ]]; then
	./web "$web_dir/main.html" "$web_dir/header" >> "$log_dir/setup.out" 2>> "$log_dir/error.out" || exit 1
	if [ ! -z $? ]; then
		echo 1 > "$log_dir/state.out"
	fi

else 
	echo server already running >> "$log_dir/setup.out"
fi

exit 0