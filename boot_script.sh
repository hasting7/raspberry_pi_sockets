#!/bin/bash

# 1 -> path
cd $1

rm error.out
rm setup.out
rm SERVER_STATE

./ready

echo 0 > SERVER_STATE
echo "server reset" >> setup.out

