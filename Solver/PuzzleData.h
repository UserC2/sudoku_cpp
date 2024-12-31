#ifndef PUZZLEDATA_SUDOKU_H
#define PUZZLEDATA_SUDOKU_H

#include "constants.h"
#include <array>
#include <initializer_list>
#include <iostream> // temp

// should solver be written with Cells? nope use ints
// Board class should handle everything related to Cells.
// Cell class shouldn't exist
// if so, Cell shouldn't know of ncurses, and all movement should be handled outside of Cell. Otherwise it would rangomly move the cursor in Solver.
// HANDLE HINT CELLS
// maybe Board has a seperate PuzzleData consisting of hints and prevents updating them if it matches?

class PuzzleData final
{
private:
	std::array<std::array<int, 9>, 9> m_grid;
	int m_rows{ 9 };
	int m_columns{ 9 };

public:
	PuzzleData() = default; // probably shouldn't exist
	PuzzleData(std::initializer_list<std::initializer_list<int>> list)
		: m_rows{ static_cast<int>(m_grid.size()) }
		, m_columns{ static_cast<int>(m_grid.at(0).size()) }
	{
		int rowCount{ 0 };
		for (std::initializer_list<int> row : list)
		{
			int columnCount{ 0 };
			for (int cell : row)
			{
				m_grid.at(rowCount).at(columnCount) = cell;
				columnCount++;
			}
			rowCount++;
		}
	}

	// need one of these for a file??

	void erase(int row, int column)
	{
		update(row, column, constants::erase_value);
	}

	void print() const
	{
		for (auto row : m_grid)
		{
			for (auto cell : row)
			{
				std::cout << cell << ' ';
			}
			std::cout << '\n';
		}
	}	

	// m_grid is an array
	// each std::array is a row
	// each item in the std::array is a cell

	void update(int row, int column, int number)
	{
		m_grid.at(row).at(column) = number;
	}

	// :( note: erase cell before going here
	// need to make this ignore the selected cell
	bool valid(int row, int column, int number) const
	{
		// rows:
		for (auto cell : m_grid.at(row))
		{
			std::cerr << "cell: " << cell << '\n';
			if (cell == number) return false;
		}
		std::cerr << "passed rows\n";
		// columns:
		for (int i{ 0 }; i < m_rows; i++)
		{
			if (m_grid.at(i).at(column) == number) return false;
		}
		std::cerr << "passed cols\n";
		// squares:
		int squareX{ (column / constants::square_size) * 3 };
		int squareY{ (row / constants::square_size) * 3 };
		std::cerr << "squareX: " << squareX << '\n';
		std::cerr << "squareY: " << squareY << '\n';
		for (int y{ 0 }; y < 3; y++)
		{
			for (int x{ 0 }; x < 3; x++)
			{
				if (m_grid.at(squareY + y).at(squareX + x) == number)
					return false;
			}
		}
		return true;
	}

	int value(int row, int column)
	{
		return m_grid.at(row).at(column);
	}
};

#endif
