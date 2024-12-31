#include "input.h"
#include <functional>
#include <iostream>
#include <limits> // yeah I forgot this...
#include <string>
#include <string_view>

// namespaces are typically lowercase... I changed this to match
namespace input
{
	/* Returns false if user enters quitString, otherwise returns true after
	* user presses enter. Case sensitive. */
	bool askToContinue(std::string_view prompt, std::string_view quitString)
	{
		std::cout << prompt;
		std::string input{};
		std::getline(std::cin, input); // no std::ws so user can press enter
		return input != quitString;
	}

	/* Loops until user enters Y/y or N/n. Returns true if Y/y, false if N/n */
	bool chooseYOrN(std::string_view prompt)
	{
		while (true)
		{
			char input{ getInput<char>(prompt) };
			switch (input)
			{
			case 'y':
			case 'Y':
				return true;
			case 'n':
			case 'N':
				return false;
			default:
				invalidInput();
//				continue;
			}
		}
	}

	/* For use within input.cpp. I guess you could use it. */
	void ignoreLine()
	{
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	/* Ignore characters until the delimiter is found (and ignore it too). */
	void ignoreUntil(char delimiter)
	{
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), delimiter);
	}

	/* Prompt user that input was invalid. */
	void invalidInput()
	{
		std::cout << "Invalid input.\n";
	}

	/* Get full line of input as a string, no input validation.
	* Manually call invalidInput() if the user enters invalid input. */
	std::string getSInput(std::string_view prompt)
	{
		// std::getline doesn't like to work with template functions
		std::cout << prompt;
		std::string input{};
		std::getline(std::cin >> std::ws, input);
		return input;
	}

	/* Get full line of input as a string, no input validation.
	* Manually call invalidInput() if the user enters invalid input. */
	template <>
	std::string getInput<std::string>(std::string_view prompt)
	{
		std::cout << prompt;
		std::string input{};
		std::getline(std::cin >> std::ws, input);
		return input;
	}
}
