/************************************************************
* Name:  Sujil Maharjan                                    *
* Project : Project 1, Duell game                          *
* Class : Organization of Programming Language(CMPS 366-01)*
* Date : 10-5-2016                                         *
************************************************************/
#pragma once
#include<iostream>
#include"Board.h"

class BoardView
{
public:
	BoardView();
	~BoardView();

	bool setBoard(Board * givenBoard);

	void printBoard();

private:
	Board * board;
};

