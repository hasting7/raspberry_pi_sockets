#!/bin/bash

# 1 -> path
log_dir="server-logs"

cd "$1/$log_dir"
pwd

rm error.out
rm setup.out 
rm state.out

cd ".."
pwd

./ready

echo 0 > "$log_dir/state.out"
echo "server reset" >> "$log_dir/setup.out"

