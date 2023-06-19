#!/bin/bash
if ! [ -d "./.temp/" ]; then
    mkdir ./.temp
fi
#$(pkg-config gtkmm-2.4 --cflags)
clear
g++ $1.cpp -lglfw -lGL -lGLEW -g -o .temp/$1 -lm

size=$(find "./.temp/$1" -printf "%s")
echo "Compiled file size ($((size/1000)) Kb)".

sleep 1

./.temp/$1