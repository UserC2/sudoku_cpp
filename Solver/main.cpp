#include "PuzzleData.h"
#include <ncurses.h>

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
	PuzzleData data{
	{ 5, 3, 4, 6, 7, 8, 9, 1, 2 },
	{ 6, 7, 2, 1, 9, 5, 3, 4, 8 },
	{ 1, 9, 8, 3, 4, 2, 5, 6, 7 },
	{ 8, 5, 9, 7, 6, 1, 4, 2, 3 },
	{ 4, 2, 6, 8, 5, 3, 7, 9, 1 },
	{ 7, 1, 3, 9, 2, 4, 8, 5, 6 },
	{ 9, 6, 1, 5, 3, 7, 2, 8, 4 },
	{ 2, 8, 7, 4, 1, 9, 6, 3, 5 },
	{ 3, 4, 5, 2, 8, 6, 1, 7, 9 },
	};
	while (true)
	{
		data.print();
		std::cout << "row: ";
		int r;
		std::cin >> r;
		std::cout << "col: ";
		int c;
		std::cin >> c;
		std::cout << "num: ";
		int n;
		std::cin >> n;
		data.erase(r, c);
		bool result{ data.valid(r, c, n) };
		std::cout << "result: ";
		if (result) std::cout << "true\n";
		else std::cout << "false\n";
		std::cout << "Q to quit ";
		char quit;
		std::cin >> quit;
		if (quit == 'q') break;
	}
//	initscr();
/*	WINDOW* win = newwin(constants::win_height, constants::win_width, 0, 0);
	cursesInit(win);

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
			moveRight(win);
		}
		wrefresh(win);
	}
*/
//	endwin();
	return 0;
}
