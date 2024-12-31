#ifndef SUDOKU_FILE_PARSER_H
#define SUDOKU_FILE_PARSER_H

#include <array>
#include <iostream>
#include <limits>
#include <string>
#include <string_view>
#include <vector>
#include "FstreamHandler.h"
#include "newinput.h"

// ignore this for now
class Puzzle {
public:
	enum class CellIndex {
		value = 0,
		row = 1,
		column = 2,
	}
	using cell_t = std::array<int, 3>;
	using hints_t = std::vector<cell_t>;
	// row, column
	using puzzle_t = std::array<std::array<int, 9>, 9>;

private:
	const std::string m_name;
	const std::string m_author;
	puzzle_t m_data;

public:
	Puzzle() = default;
	Puzzle(hints_t hints, std::string_view name, std::string_view author)
		: m_name{ name }
		, m_author{ author }
		, m_data{ std::array() }
	{
		for (cell_t hint : hints)
		{
			setCell(hint);
		}
	}
	Puzzle(FstreamHandler& file)
		: m_name{ parseName(file) }
		, m_author{ parseAuthor(file) }
		, m_data{ parseData(file) }
	{}

// type aliases instead of int???
	int getCell(int row, int column) const { m_data.at(row).at(column); }

	void setCell(cell_t cell)
	{
		setCell(
			cell.at(CellIndex.value),
			cell.at(CellIndex.row),
			cell.at(CellIndex.column)
		);
	}
	
	void setCell(int value, int row, int column)
	{
		m_data.at(row).at(column) = value;
	}
	// how keep track of hints?

private:
	std::string parseName(FstreamHandler& file) static const
	{
		if (input::ignoreUntil('='))
		{
			std::cerr << "FILE PARSE ERROR: Missing Name in:" 
				+ static_cast<std::string>(file.filename()) + '\n';
			return "PARSE_ERROR";
		}
		std::string name{};
		std::getline(file.stream() << std::ws, name);
		return name;
	}
	std::string parseAuthor(FstreamHandler& file) static const
	{
		if (input::ignoreUntil('=')) // need to check if it matches `AUTHOR` first...
		{
			std::cerr << "FILE PARSE ERROR: Missing Name in:" 
				+ static_cast<std::string>(file.filename()) + '\n';
			return "PARSE_ERROR";
		}
		std::string name{};
		std::getline(file.stream() << std::ws, name);
		return name;
	}
	hints_t parseData(FstreamHandler& file) static const
	{
	// 	// repeat for rows/columns
	}

	namespace input
	{
		// true on fail
		boolean ignoreUntil(FstreamHandler& file, char delimiter) static const
		{
			file.stream().ignore(std::numeric_limits<std::streamsize>::max(), delimiter);
			if (file.stream().fail())
			{
				file.stream().clear()
				return true;
			}
			return false;
		}
		// TODO: check EOF
	}
};
#endif