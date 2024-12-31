#ifndef C2_INCLUDE_INPUT_H
#define C2_INCLUDE_INPUT_H
#include <functional>
#include <iostream>
#include <string_view>

// NEW INPUT

// compile input.cpp with your project!
// namespaces are typically lowercase... I changed this to match
namespace input
{
	/* Returns false if user enters quitString, otherwise returns true after
	* user presses enter. Case sensitive. */
	bool askToContinue(std::string_view prompt, std::string_view quitString);

	/* Loops until user enters Y/y or N/n. Returns true if Y/y, false if N/n */
	bool chooseYOrN(std::string_view prompt);

	/* For use within input.cpp. I guess you could use it. */
	void ignoreLine();

	/* Ignore characters until the delimiter is found (and ignore it too). */
	void ignoreUntil(char delimiter);

	/* Prompt user that input was invalid. */
	void invalidInput();

	/* Checks if std::cin fails, if it does, prompts user to enter again.
	* Make sure to specify type it should return in < > between name and () */
	template <typename T>
	T getInput(std::string_view prompt)
	{
		while (true)
		{
			std::cout << prompt;
			T input{}; // this is annoying
			std::cin >> input;

			// Input validation
			if (std::cin.fail())
			{
				std::cin.clear();
				ignoreLine();
				invalidInput();
			}
			else
			{
				ignoreLine();
				return input;
			}
		}
	}

	/* Get full line of input as a string, no input validation.
	* Manually call invalidInput() if the user enters invalid input. */
	template <>
	std::string getInput<std::string>(std::string_view prompt);
}
#endif
