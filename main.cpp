#include "constants.h"
#include <ncurses.h>
#include <array>
#include <cassert>

// modify to use base 9 num instead of char for token, then to print you can convert token using switch statement
class Cell
{
private:
	chtype m_token{ static_cast<chtype>('0') };
	bool m_isHintCell{ false };

public:
	Cell() = default;
	/* Hint cells are non-modifiable and have a different appearance. */
	Cell(chtype token, bool isHintCell)
		: m_token{ (isHintCell ? token | A_REVERSE : token) }
		// A_BOLD?
		, m_isHintCell{ isHintCell }
	{}

	/* Print token to current cursor position */
	void print(WINDOW* win) const { waddch(win, m_token); }
	/* Return current token */
	chtype token() const { return m_token; }
	/* Change token to 'ch'. */
	void update(WINDOW* win, chtype ch) 
	{ 
		if (m_isHintCell) return;
		m_token = ch & A_CHARTEXT;
		print(win);
	}
};

class Grid
{
private:
	// I guarantee there is a std type that does this
	Cell array[9][9]{};
	Cell outOfRange{ 9, true };
	// ^ replace with assert later (user shouldn't be able to select invalid cell)

private:
	void printSquare(WINDOW* win, int x, int y) const // x, y of square, start at 0 (e.g. middle: 1, 1)
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

public:
	Cell& findCell(WINDOW* win)
	{
		int y;
		int x;
		getyx(win, y, x);
		if (y > 8 || x > 8)
			return outOfRange;
		return array[x][y];
	}

	void print(WINDOW* win) const
	{
		wclear(win);
		// for (int y{ 0 }; y < 3; y++)
		// {
		// 	for (int x{ 0 }; x < 3; x++)
		// 	{
		// 		printSquare(win, x, y);
		// 	}
		// 	wmove(win, getcury(win) + 3, 0);
		// }
		// wmove(win, 10, 0);
		// Cell c{ 48, true };
		// waddch(win, c.token());
		for (int y{ 0 }; y < 9; y++)
		{
			if ((y == 3) || (y == 6))
			{
				wprintw(win, constants::hDivider);
				wprintw(win, "\n");
			}
			wprintw(win, "%c %c %c | %c %c %c | %c %c %c\n", array[0][y],
				array[1][y], array[2][y], array[3][y], array[4][y],
				array[5][y], array[6][y], array[7][y], array[8][y]);
		}
		wmove(win, 0, 0);
		/*
		for (int y{ 0 }; y < 9; y++)
		{
			for (int x{ 0 }; x < 9; x++)
			{
				wprintw(win, "%c", array[x][y].value());
			}
			wprintw(win, "\n");
		}
		*/
		/*
		for (int a{ 1 }; a < 4; a++)
		{
			for (int y{ 1 }; y < 4; y++)
			{
				for (int b{ 1 }; b < 4; b++)
				{
					for (int x{ 1 }; x < 4; x++)
					{
						wprintw(win, "%c ", array[(x * b) - 1][(y * a) - 1].value());
					}
					if (b < 3) wprintw(win, "| ");
				}
				wprintw(win, "\n");
			}
			if (a < 3) wprintw(win, "- - -   - - -   - - -\n");
		}
		*/
	}

	/* Print an empty grid. Call this once before any calls to print(). */
	void printBase(WINDOW* win) const
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
			wprintw(win, constants::hDivider);
		}
		wmove(win, 0, 0);
	}
};

void moveLeft(WINDOW* win)
{
	int y;
	int x;
	getyx(win, y, x);
	int movement{ ((x == 8) || (x == 16)) ? x - 4 : x - 2 };
	wmove(win, y, movement);
}

void moveRight(WINDOW* win)
{
	int y;
	int x;
	getyx(win, y, x);
	int movement{ ((x == 4) || (x == 12)) ? x + 4 : x + 2 };
	wmove(win, y, movement);
}

void moveUp(WINDOW* win)
{
	int y;
	int x;
	getyx(win, y, x);
	int movement{ ((y == 4) || (y == 8)) ? y - 2 : y - 1 };
	wmove(win, movement, x);
}

void moveDown(WINDOW* win)
{
	int y;
	int x;
	getyx(win, y, x);
	int movement{ ((y == 2) || (y == 6)) ? y + 2 : y + 1 };
	wmove(win, movement, x);
}

void confirmNum()
{
	printw("confirm");
}

void delNum()
{
	printw("del");
}

bool keyIsNumber(chtype ch)
{
	ch = ch & A_CHARTEXT;
	return (ch >= '1' && ch <= '9');
}

void cursesInit(WINDOW* w=stdscr)
{
	raw();
	noecho(); // only print char if it is a number
	keypad(w, TRUE); // arrow keys
	// nonl(); // only makes return output '\r' instead of '\n', not needed
	scrollok(w, FALSE); // no scrolling allowed
}

int main()
{
	initscr();
	WINDOW* win = stdscr;
	cursesInit(win);
	Grid grid;

	chtype ch{ 0 };
	while ((ch = wgetch(win)) != constants::exit_key)
	{
		switch (ch)
		{
		case KEY_LEFT:
		case 'a':
			moveLeft(win);
			break;
		case KEY_RIGHT:
		case 'd':
			moveRight(win);
			break;
		case KEY_UP:
		case 'w':
			moveUp(win);
			break;
		case KEY_DOWN:
		case 's':
			moveDown(win);
			break;
		case KEY_ENTER:
		case '\n':
		case '\r':
			confirmNum();
			break;
		case KEY_BACKSPACE:
		case constants::backspace_keycode:
		case '\b':
			delNum();
			break;
		case constants::print_key:
			grid.print(win);
			//grid.printBase(win);
			break;
		default:
			break; // move on if no matching keys
		}
		if (keyIsNumber(ch))
		{
			grid.findCell(win).update(win, ch);
		}
		refresh();
	}

	endwin();
	return 0;
}