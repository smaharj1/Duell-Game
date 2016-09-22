#pragma once

#include<iostream>
#include"boardView.h"
#include"Board.h"
#include"player.h"
#include"human.h"
#include "computer.h"

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
	bool computerWin;

	player * humanP;
	player * bot;

	void printMove(int row, int col, int newRow, int newCol, bool isComputer);
	bool isMoveLegal(int row, int col, int newRow, int newCol, bool isComputer);
	bool isPathLegal(int row, int col, int newRow, int newCol, bool correctPaths[]);

	const int MAX_ROW = 9;

};

