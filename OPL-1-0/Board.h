#pragma once

#include"Dice.h"
#include"Cell.h"

class Board
{
public:
	Board();
	~Board();

	void printBoard();
	

private:
	Cell * board[8][9];
	
	const int ROWS = 8;
	const int COLUMNS = 9;
};

