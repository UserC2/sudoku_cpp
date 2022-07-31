#include "Cell.h"
#include "constants.h"
#include <ncurses.h>

Cell::Cell(chtype token, bool isHintCell)
	: m_token{ (isHintCell ? token | A_REVERSE : token) }
	// A_BOLD?
	, m_isHintCell{ isHintCell }
{
}

void Cell::erase(WINDOW* win) 
{
	m_token = constants::erase_value;
	print(win);
}

void Cell::print(WINDOW* win) const 
{ 
	int x{ getcurx(win) };
	int y{ getcury(win) };
	waddch(win, m_token); 
	wmove(win, y, x);
}

void Cell::update(WINDOW* win, chtype ch) 
{ 
	if (m_isHintCell) return;
	m_token = ch & A_CHARTEXT;
	print(win);
}