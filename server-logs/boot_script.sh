#!/bin/bash

# 1 -> path
log_dir="server-logs"

cd "$1/$log_dir"

rm -f error.out && touch error.out
rm -f setup.out 
rm -f state.out

cd ".."

./ready

echo 0 > "$log_dir/state.out"
echo "server reset" >> "$log_dir/setup.out"

cd $log_dir

./initalize_server.sh ..

