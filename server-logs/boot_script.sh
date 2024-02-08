#!/bin/bash

# 1 -> path
log_dir="server-logs"
web_dir="web-src"

cd "$1/$log_dir"

rm -f error.out && touch error.out
rm -f setup.out 
rm -f state.out

cd ".."

./ready

echo 0 > "$log_dir/state.out"
echo "server reset" >> "$log_dir/setup.out"


for file in "state.out" "setup.out"; do
	if [ ! -e "$log_dir/$file" ]; then
		echo "$file DNE" >> "$log_dir/error.out" 
		exit 1
	fi
	echo "$log_dir/$file found" >> "$log_dir/setup.out" 
done
for file in "header" "main.html"; do
	if [ ! -e "$web_dir/$file" ]; then
		echo "$file DNE" >> "$log_dir/error.out" 
		exit 1
	fi
	echo "$web_dir/$file found" >> "$log_dir/setup.out" 
done
echo "files validated" >> "$log_dir/setup.out"

# cd "$log_dir"
# ./initalize_server.sh .. || echo "server set from boot failed " >> error.out
./web "$web_dir/main.html" "$web_dir/header" > "$log_dir/setup.out" 2> "$log_dir/error.out"
