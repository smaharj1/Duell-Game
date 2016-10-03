/************************************************************
* Name:  Sujil Maharjan                                    *
* Project : Project 1, Duell game                          *
* Class : Organization of Programming Language(CMPS 366-01)*
* Date : 10-5-2016                                         *
************************************************************/
#pragma once

#include"Dice.h"
#include"Cell.h"

/*
	This class performs all the functions that are related to making any changes or verifictaions of the board. 
	This is a model class that allows to verify every movement according to players. This class is fully functional.
*/
class Board
{
public:
	// Default constructor for new game.
	Board();

	// Constructor for starting a loaded game where we get the arrays of existing dices on the board.
	Board(Dice ** human, Dice ** bot);
	~Board();
	
	// Returns the total number of rows and columns on the board.
	int getTotalRows() { return ROWS; }
	int getTotalColumns() { return COLUMNS; }

	// Moves the dice from one location to another that are provided as the parameter and moves it in the direction chosen by the user.
	Dice * move(int row, int col, int newRow, int newCol, char direction);

	// Initialization starts from 0;
	Cell * getCell(int row, int col) { return board[row][col]; }

	// checks if the move made is legal. The parameter ints are user friendly i.e. the index starts from 0.
	bool isLegal(int row, int column, int newRow, int newCol, bool isComputer);

	// Checks if there are any hindrances in the path from one location to another.
	bool isPathGood(int row, int col, int newRow, int newCol, bool correctPaths[]);

	// Checks the path for algorithmic approach.
	bool checkPathForAlgo(int row, int col, int newRow, int newCol, bool isGodMode);

	// Checks if the move is legal for algorithmic approach. This is a backdoor for machine.
	bool isLegalAlgo(int row, int column, int newRow, int newCol, bool isComputer);

	// Moves the dice through algorithm.
	Dice * moveFromAlgo(int row, int col, int newRow, int newCol);

	// Sets the board.
	bool setBoard(string tempBoard[][9]);

	// Sets if the functions are being run as a god mode.
	bool setGodMode(bool given);
	bool getIfGodMode() { return isGodMode; }

private:
	// Private array that holds the board.
	Cell * board[8][9];
	
	// Constants that hold the statistics of the board.
	const int ROWS = 8;
	const int COLUMNS = 9;
	const int ROW_LOW_LIMIT = 1;
	const int ROW_HIGH_LIMIT = 8;
	const int COLUMN_LOW_LIMIT = 1;
	const int COLUMN_HIGH_LIMIT = 9;

	bool isGodMode;

};

