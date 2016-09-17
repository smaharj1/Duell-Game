#pragma once
#include<iostream>
#include"Board.h"

class BoardView
{
public:
	BoardView();
	~BoardView();

	void setBoard(Board * b) {
		board = b;
	}

	void printBoard();

private:
	Board * board;
};

