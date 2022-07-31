#include "constants.h"
#include "Grid.h"
#include <ncurses.h>

void moveLeft(WINDOW* win)
{
	int y;
	int x;
	getyx(win, y, x);
	if (x == 0)
	{
		int movement{ ((y == 5) || (y == 9)) ? y - 2 : y - 1 };
		wmove(win, movement, getmaxx(win) - 1);
	}
	else
	{
		int movement{ ((x == 8) || (x == 16)) ? x - 4 : x - 2 };
		wmove(win, y, movement);
	}
}

void moveRight(WINDOW* win)
{
	int y;
	int x;
	getyx(win, y, x);
	if (x == getmaxx(win) - 1)
	{
		int movement{ ((y == 2) || (y == 6)) ? y + 2 : y + 1 };
		wmove(win, movement, 0);
	}
	else
	{
		int movement{ ((x == 4) || (x == 12)) ? x + 4 : x + 2 };
		wmove(win, y, movement);
	}
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
	WINDOW* win = newwin(constants::win_height, constants::win_width, 0, 0);
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
		case KEY_ENTER:
		case '\n':
		case '\r':
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
		case KEY_BACKSPACE:
		case constants::backspace_keycode:
		case '\b':
			grid.findCell(win).erase(win);
			break;
		case constants::print_key:
			grid.print(win);
			break;
		default:
			break; // move on if no matching keys
		}
		if (keyIsNumber(ch))
		{
			grid.findCell(win).update(win, ch);
		}
		wrefresh(win);
	}

	endwin();
	return 0;
}