#!/bin/bash
rm ./date.o
echo "========================================="
g++ -std=c++0x -o date.o date.cpp kattistime.cpp main.cpp gregorian.cpp julian.cpp
#g++ -std=c++0x -o date.o date.cpp kattistime.cpp cprog09lab22b.cpp gregorian.cpp
echo "========================================="
#valgrind --tool=memcheck --leak-check=yes ./date.o
./date.o
echo "========================================="
