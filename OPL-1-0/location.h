/************************************************************
* Name:  Sujil Maharjan                                    *
* Project : Project 1, Duell game                          *
* Class : Organization of Programming Language(CMPS 366-01)*
* Date : 10-5-2016                                         *
************************************************************/
#pragma once

/*
	This class holds the value of location on the board.
*/
class location
{
public:
	// Constructor that defines the row and the column
	location(int tempRow, int tempCol);
	~location();

	// Gets the row and columns.
	int getRow() { return row; }
	int getColumn() { return col; }

private:
	// private variables that holds row and column information.
	int row;
	int col;
};

