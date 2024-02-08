#!/bin/bash

# 1 -> path
cd "$1/server-logs"
echo "$1/server-logs"

rm error.out
rm setup.out
rm state.out

./ready

echo 0 > state.out
echo "server reset" >> setup.out

