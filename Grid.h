#ifndef SUDOKU_GRID_H
#define SUDOKU_GRID_H

#include "Cell.h"
#include <ncurses.h>
//#include <array>
#include <map>

class Grid final
{
private:
	Cell array[9][9]{}; // std::array? // alternatively, make this a seperate type so that it can be used by the text interface header
	const static std::map<int, int> xMap;

public:
	Grid()
	{
	}

private:
	/* Print one sudoku square, x, y are of square, start at 0, 0. */
	void printSquare(WINDOW* win, int x, int y) const;

public:
	/* Return a reference to the cell at the current cursor location. */
	Cell& findCell(WINDOW* win);
	/* Print the grid and its contents */
	void print(WINDOW* win) const;
	/* Print an empty grid. */
	// void printBase(WINDOW* win) const;
};

#endif