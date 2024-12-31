#include "Board.h"
#include "Cell.h"
#include "constants.h"
#include <ncurses.h>
#include <cassert>
#include <map>

void Board::printSquare(WINDOW* win, int x, int y) const
{
	int oy;
	int ox;
	getyx(win, oy, ox);
	x *= 3; // 3
	y *= 3; // 0
	for (int ly{ 0 }; ly < 3; ly++)
	{
		for (int lx{ 0 }; lx < 3; lx++)
		{
			waddch(win, array[lx + x][ly + y].token());
		}
		int yy, xx;
		getyx(win, yy, xx);
		wmove(win, yy + 1, ox);
	}
	wmove(win, oy, ox + 3);
}

Cell& Board::findCell(WINDOW* win)
{
	int y;
	int x;
	getyx(win, y, x);
	if (y > constants::win_height || x > constants::win_width)
	{
		// make this valid:
		// invalid ranges:
		// y 3, 7
		// x 5, 6, 7, 13, 14, 15
		assert(false && "Invalid Grid Cell");
	}
	// horizontal borders
	if (y > 3) y--;
	if (y > 6) y--;
	return array[m_xMap.at(x)][y];
}

void Board::print(WINDOW* win) const
{
	wclear(win);
	wmove(win, 0, 0);
	for (int y{ 0 }; y < 9; y++)
	{
		if ((y == 3) || (y == 6))
		{
			wprintw(win, constants::h_divider);
			wmove(win, getcury(win), 0);
			// ^ wprintw moves to new line when it reaches end of window
		}
		// works fine because the divider is printed then the loop CONTINUES
		wprintw(win, "%c %c %c | %c %c %c | %c %c %c", array[0][y],
			array[1][y], array[2][y], array[3][y], array[4][y],
			array[5][y], array[6][y], array[7][y], array[8][y]);
			wmove(win, getcury(win), 0);
	}
	wmove(win, 0, 0);
}

/*
void Grid::printBase(WINDOW* win) const
{
	wmove(win, 0, 0);
	// print vertical dividers
	for (int x{ 6 }; x < 15 ; x += 8)
	{
		for (int y{ 0 }; y < 9; y += 4)
		{
			mvwvline(win, y, x, '|', 3);
			wmove(win, getcury(win) + 1, getcurx(win));
			mvwvline(win, y, x, '|', 3);
			wmove(win, getcury(win) + 1, getcurx(win));
			mvwvline(win, y, x, '|', 3);
		}
	}
	// print horizontal dividers
	for (int y{ 3 }; y < 8 ; y += 4)
	{
		wmove(win, y, 0);
		wprintw(win, constants::h_divider);
	}
	wmove(win, 0, 0);
}
*/

const std::map<int, int> Board::m_xMap
{ 
	{ 0, 0 },
	{ 2, 1 },
	{ 4, 2 },
	{ 8, 3 },
	{ 10, 4 },
	{ 12, 5 },
	{ 16, 6 },
	{ 18, 7 },
	{ 20, 8 },
};