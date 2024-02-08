#!/bin/bash

cd server-logs
echo --------Server State--------
cat state.out
echo --------Server Setup--------
cat setup.out
echo --------Sever Errors--------
cat error.out
exit 0