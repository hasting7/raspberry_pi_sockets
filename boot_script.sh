#!/bin/bash

# 1 -> path
$1/ready

echo 0 > $1/SERVER_STATE
echo "server reset"

