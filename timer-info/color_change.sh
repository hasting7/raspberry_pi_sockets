#!/bin/bash

#1 -> ip or localhost
#2 -> port
#3 -> color

curl $1:$2\?color=$3 || exit 1
exit 0