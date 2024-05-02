#!/bin/bash

g++ -o bookworms main.cpp menu.cpp database.cpp -lmysqlclient

if [ $? -eq 0 ]; then
    ./bookworms
else
    echo "WOMP WOMP"
fi