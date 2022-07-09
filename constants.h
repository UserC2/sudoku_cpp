#include <ncurses.h>

namespace constants
{
	constexpr chtype exit_key{ static_cast<chtype>('~') };
	constexpr chtype print_key{ static_cast<chtype>('P') };
	constexpr int backspace_keycode{ 127 };
}