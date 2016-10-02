#pragma once

#include"Dice.h"
#include"Cell.h"



class Board
{
public:
	Board();
	Board(Dice ** human, Dice ** bot, int size);
	~Board();
	
	int getTotalRows() { return ROWS; }
	int getTotalColumns() { return COLUMNS; }
	Dice * move(int row, int col, int newRow, int newCol, char direction);

	// Initialization starts from 0;
	Cell * getCell(int row, int col) { return board[row][col]; }

	bool isLegal(int row, int column, int newRow, int newCol, bool isComputer);
	bool isPathGood(int row, int col, int newRow, int newCol, bool correctPaths[]);
	bool checkPathForAlgo(int row, int col, int newRow, int newCol, bool isGodMode);
	Dice * moveFromAlgo(int row, int col, int newRow, int newCol);

	void setBoard(string tempBoard[][9]);

private:
	Cell * board[8][9];
	
	const int ROWS = 8;
	const int COLUMNS = 9;

	const int ROW_LOW_LIMIT = 1;
	const int ROW_HIGH_LIMIT = 8;
	const int COLUMN_LOW_LIMIT = 1;
	const int COLUMN_HIGH_LIMIT = 9;

	bool godMode;

};

