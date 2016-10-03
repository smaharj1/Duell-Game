/************************************************************
* Name:  Sujil Maharjan                                    *
* Project : Project 1, Duell game                          *
* Class : Organization of Programming Language(CMPS 366-01)*
* Date : 10-5-2016                                         *
************************************************************/
#pragma once

#include"Dice.h"
#include"Cell.h"

class Board
{
public:
	Board();
	Board(Dice ** human, Dice ** bot);
	~Board();
	
	int getTotalRows() { return ROWS; }
	int getTotalColumns() { return COLUMNS; }
	Dice * move(int row, int col, int newRow, int newCol, char direction);

	// Initialization starts from 0;
	Cell * getCell(int row, int col) { return board[row][col]; }

	bool isLegal(int row, int column, int newRow, int newCol, bool isComputer);
	bool isPathGood(int row, int col, int newRow, int newCol, bool correctPaths[]);
	bool checkPathForAlgo(int row, int col, int newRow, int newCol, bool isGodMode);
	bool isLegalAlgo(int row, int column, int newRow, int newCol, bool isComputer);
	Dice * moveFromAlgo(int row, int col, int newRow, int newCol);

	bool setBoard(string tempBoard[][9]);
	bool setGodMode(bool given);
	bool getIfGodMode() { return isGodMode; }

private:
	Cell * board[8][9];
	
	const int ROWS = 8;
	const int COLUMNS = 9;

	const int ROW_LOW_LIMIT = 1;
	const int ROW_HIGH_LIMIT = 8;
	const int COLUMN_LOW_LIMIT = 1;
	const int COLUMN_HIGH_LIMIT = 9;

	bool isGodMode;

};

