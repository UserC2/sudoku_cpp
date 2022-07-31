#!/bin/bash

source="./main.cpp ./Cell.cpp ./Board.cpp"

g++ -std=c++20 -Wall -I./ $source -lncurses -o sudoku