#!/bin/bash

# 1 -> path
log_dir="server-logs"


rm error.out
rm setup.out
rm state.out

./ready

echo 0 > "$log_dir/state.out"
echo "server reset" >> "$log_dir/setup.out"

