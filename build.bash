#!/bin/bash
#set -u -e
#make clean
make opt
echo "Running..."
cd ../bin
./obj 960
