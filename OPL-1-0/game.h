/************************************************************
* Name:  Sujil Maharjan                                    *
* Project : Project 1, Duell game                          *
* Class : Organization of Programming Language(CMPS 366-01)*
* Date : 10-5-2016                                         *
************************************************************/
#pragma once

#include<iostream>
#include"boardView.h"
#include"Board.h"
#include"player.h"
#include"human.h"
#include "computer.h"
#include<fstream>
#include"FileHandler.h"
#include<time.h>

using namespace std;

class game
{
public:
	game();
	~game();
	game(Board * tempBoard, bool computersTurn);

	bool isComputerWinner();
	bool startGame();

	Board * getBoard() { return board; }
	bool getIfComputerTurn() { return isComputersTurn; }


private:
	BoardView boardView;
	Board * board;
	bool isComputersTurn;
	bool isDone;
	bool computerWin;
	char userInputForSaving;
	

	player * humanP;
	player * bot;

	void determineTurn();
	int rollDie();

	const int MAX_ROW = 9;

};

