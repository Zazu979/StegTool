#!/bin/bash

if [[ "$1" == "-v" ]]; then
   cmake . 
   make clean 
   make 
   ./StegTool -i ./img/icy.png -o ./img/out.png -f ./txt/test.txt 
   ./StegTool -d -i ./img/out.png -o ./txt/out.txt 
else   
   cmake . >/dev/null
   make clean >/dev/null
   make >/dev/null
   ./StegTool -i ./img/icy.png -o ./img/out.png -f ./txt/test.txt >/dev/null
   ./StegTool -d -i ./img/out.png -o ./txt/out.txt >/dev/null
fi

diff=$(diff ./txt/test.txt ./txt/out.txt)

if [ "$diff" == "" ]; then
   echo "It works"
else
   echo "It's Broken"
fi