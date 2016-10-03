/************************************************************
* Name:  Sujil Maharjan                                    *
* Project : Project 1, Duell game                          *
* Class : Organization of Programming Language(CMPS 366-01)*
* Date : 10-5-2016                                         *
************************************************************/
#pragma once
#include<iostream>
#include"Board.h"

/*
	This is the view of the board.
*/
class BoardView
{
public:
	// Default constructor.
	BoardView();
	~BoardView();

	// Sets the board for display.
	bool setBoard(Board * givenBoard);

	// Prints the board.
	void printBoard();

private:
	Board * board;
};

