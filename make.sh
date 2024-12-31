#!/bin/bash

# replace this with the location of UserC2/include
externPath="../../include/"

externIncludes="${externPath}FstreamHandler.cpp"

source="./main.cpp ./Cell.cpp ./Board.cpp ./newinput.cpp"

g++ -std=c++20 -Wall -Werror -I./ -I$externPath $externIncludes $source -lncurses -o sudoku