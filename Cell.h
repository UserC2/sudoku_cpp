#ifndef SUDOKU_CELL_H
#define SUDOKU_CELL_H

#include "constants.h"
#include <ncurses.h>

// modify to use base 9 num instead of char for token, then to print you can convert token using switch statement
// actually use base 10 (0 for invalid) so that 1 value can be blank
class Cell final
{
private:
	chtype m_token{ constants::erase_value };
	bool m_isHintCell{ false };

public:
	Cell() = default;
	/* Hint cells are non-modifiable and have a different appearance. */
	Cell(chtype token, bool isHintCell);
	/* Erase cell and print value */
	void erase(WINDOW* win);
	/* Print token to current cursor position */
	void print(WINDOW* win) const;
	/* Return current token */
	chtype token() const { return m_token; }
	/* Change token to 'ch'. */
	void update(WINDOW* win, chtype ch);
};

#endif