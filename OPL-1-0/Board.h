#pragma once

#include"Dice.h"
#include"Cell.h"

class Board
{
public:
	Board();
	~Board();

	void printBoard();
	bool move(int x, int y, int frontal, int side);

private:
	Cell * board[8][9];
	
	const int ROWS = 8;
	const int COLUMNS = 9;

	const int ROW_LOW_LIMIT = 1;
	const int ROW_HIGH_LIMIT = 8;
	const int COLUMN_LOW_LIMIT = 1;
	const int COLUMN_HIGH_LIMIT = 9;
};

