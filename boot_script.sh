#!/bin/bash

# 1 -> path
cd $1

./ready

echo 0 > SERVER_STATE
echo "server reset" >> setup.out

