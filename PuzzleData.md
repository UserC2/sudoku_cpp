* How do I store the data in a puzzle to a file?

### Format #1
Need to store 9x9 array of numbers between 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 (0 = empty, don't show)
```
- - *  - - -  - - -
- - -  - - -  - - -
- - -  - - -  - - -
- - -  - - -  - - -
- - -  - * -  - - -
- - -  - - -  - - -
- - -  - - -  - - -
- - -  - - -  - * -
- - -  - - -  - - -
```
Good file format
```
NAME=PUZZLE_NAME
AUTHOR=AUTHOR_NAME
SOLUTION
1 3 7 6 9 2 8 5 4
4 9 2 7 8 5 6 1 3
6 5 8 4 1 3 2 7 9
3 6 1 9 2 4 5 8 7
2 8 9 1 5 7 3 4 6
7 4 5 8 3 6 9 2 1
5 2 6 3 7 1 4 9 8
9 7 3 2 4 8 1 6 5
8 1 4 5 6 9 7 3 2
HINTS
- - - - - - - * -
- - * - - - - - -
- - - - - - - - -
- - - - * - - - -
- - - - - - - - -
- - - - - * - - -
- - * - - - - - -
- - - - - - - - -
- - - - - * - - -
```
Parser
```
// filter will fail with parse_error if not there

filter NAME=
puzzle_name = get until newline
filter AUTHOR=
author_name = get until newline
filter SOLUTION
repeat each row (9x)
	repeat each column (9x)
		result = get char
		filter SPACE_CHAR
		switch result:
			case 0:
				cell = ERASE_CHAR
			case 1, 2, 3, 4, 5, 6, 7, 8, 9:
				cell = number
			default:
				parse_error
filter HINTS
repeat each row (9x)
	repeat each column (9x)
		result = get char
		filter SPACE_CHAR
		switch result:
			case -:
				hint_cell = false
			case *:
				hint_cell = true
			default:
				parse_error
```
inefficient

### Alternative Format
* Puzzles *can* have more than 1 solution, so checking dynamically is a good idea (also, provided soln could be bad). (However, puzzles should not have > 1 soln)
* This is still annoying to parse, as #s are useful OH IM DUMB
```
NAME=PUZZLE_NAME
AUTHOR=AUTHOR_NAME
HINT_POS
- - - - - - - * -
- - * - - - - - -
- - - - - - - - -
- - - - * - - - -
- - - - - - - - -
- - - - - * - - -
- - * - - - - - -
- - - - - - - - -
- - - - - * - - -
HINT_NUM
5 2 2 6 6 9
```
Parser
```
// filter will fail with parse_error if not there

filter NAME=
puzzle_name = get until newline
filter AUTHOR=
author_name = get until newline
filter SOLUTION
repeat each row (9x), var r
	repeat each column (9x), var c
		
		if (-)
			isHintCell = false
		if (*)
			isHintCell = true
filter HINT_NUM
repeat each hintCell



filter SOLUTION
repeat each row (9x)
	repeat each column (9x)
	result = get char
		filter SPACE_CHAR
		switch result:
			case 0:
				cell = ERASE_CHAR
			case 1, 2, 3, 4, 5, 6, 7, 8, 9:
				cell = number
			default:
				parse_error
filter HINTS
repeat each row (9x)
	repeat each column (9x)
		result = get char
		filter SPACE_CHAR
		switch result:
			case -:
				hint_cell = false
			case *:
				hint_cell = true
			default:
				parse_error
```

### FORMAT 3
```
NAME=PUZZLE_NAME
AUTHOR=AUTHOR_NAME
- - - - - - - 5 -
- - 2 - - - - - -
- - - - - - - - -
- - - - 2 - - - -
- - - - - - - - -
- - - - - 6 - - -
- - 6 - - - - - -
- - - - - - - - -
- - - - - 9 - - -
```
Parser:
```
filter NAME=
	on fail: PARSE_ERROR: MISSING NAME
puzzle_name = get_str to newline
	on fail: PARSE_ERROR: INVALID NAME
filter AUTHOR=
	on fail: PARSE_ERROR: MISSING AUTHOR
author_name = get_str to newline
	on fail: PARSE_ERROR: INVALID AUTHOR
repeat each row (9x) (var r)
	repeat each column (9x) (var c)
		result = get_char
		if (result == 1, 2, 3, 4, 5, 6, 7, 8, 9)
			// set current cell to result plz
		else if NOT (result == 0, -, *)
			PARSE_WARNING: NON-STANDARD EMPTY CELL at ROW r COL c
		filter SPACE_CHAR or NEWLINE // newline at end of column
			on fail: PARSE_WARNING: NON-STANDARD SPACING at ROW r COL c
```