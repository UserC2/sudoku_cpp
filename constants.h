#include <ncurses.h>

namespace constants
{
	constexpr int backspace_keycode{ 127 };
	constexpr int win_height{ 11 };
	constexpr int win_width{ 21 };
	constexpr char h_divider[]{ "- - -   - - -   - - -" };
	constexpr chtype erase_value{ static_cast<chtype>(' ') };
	constexpr chtype exit_key{ static_cast<chtype>('~') };
	constexpr chtype print_key{ static_cast<chtype>('P') };
}