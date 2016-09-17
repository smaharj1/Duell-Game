#pragma once

#include<iostream>
#include"boardView.h"
#include"Board.h"

using namespace std;

class game
{
public:
	game();
	~game();

	bool isComputerWinner();
	void startGame();

private:
	BoardView boardView;
	Board * board;
	bool isComputersTurn;
	bool isDone;

	bool isMoveLegal(int row, int col, int frontal, int side, bool isComputer);


};

