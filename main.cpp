#include "constants.h"
#include <ncurses.h>

void moveLeft(WINDOW* win)
{
	int y;
	int x;
	getyx(win, y, x);
	move(y, x - 1);
}

void moveRight(WINDOW* win)
{
	int y;
	int x;
	getyx(win, y, x);
	move(y, x + 1);
}

void moveUp(WINDOW* win)
{
	int y;
	int x;
	getyx(win, y, x);
	move(y - 1, x);
}

void moveDown(WINDOW* win)
{
	int y;
	int x;
	getyx(win, y, x);
	move(y + 1, x);
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
	return ch >= '0' && ch <= '9';
}

void cursesInit(WINDOW* w=stdscr)
{
	raw();
	noecho(); // only print char if it is a number
	keypad(w, TRUE); // arrow keys
	// nonl(); // only makes return output '\r' instead of '\n', not needed
	scrollok(w, FALSE); // no scrolling allowed
}

/*mvvline(1, 6, '|', 11);
mvvline(1, 13, '|', 11);
mvhline(4, 0, '-', 20);
mvhline(8, 0, '-', 20);*/

int main()
{
	initscr();
	WINDOW* win = stdscr;
	cursesInit(win);

	while (true)
	{
		int ch{ getch() };
		if (ch == constants::exit_key) break;
		switch (ch)
		{
		case KEY_LEFT:
			moveLeft(win);
			break;
		case KEY_RIGHT:
			moveRight(win);
			break;
		case KEY_UP:
			moveUp(win);
			break;
		case KEY_DOWN:
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
		}
		if (keyIsNumber(ch))
		{
			printw("num");
			// set cell to number
		}
	}
	
	endwin();
	return 0;
}