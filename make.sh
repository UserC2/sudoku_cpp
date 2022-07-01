#!/bin/bash

source="./main.cpp"

g++ -std=c++20 -Wall -I./ $source -lncurses -o sudoku