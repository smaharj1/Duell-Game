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

/*
	This class initiates the round of the tournament. It handles system of game from controlling the play as well as interacting with the view.
*/
class game
{
public:
	// Default constructor to initiate the game.
	game();
	~game();

	// Constructor if the game is started from a file instead of a new game.
	game(Board * tempBoard, bool computersTurn);

	// Checks if computer is the winner.
	bool isComputerWinner();

	// Starts the game and returns true if game is successfully ended. 
	bool startGame();

	// Gets the pointer to the board.
	Board * getBoard() { return board; }

	// Gets if it is computer's turn or not.
	bool getIfComputerTurn() { return isComputersTurn; }


private:
	// Private class variables that plays vital role in the game.
	BoardView boardView;
	Board * board;
	bool isComputersTurn;
	bool isDone;
	bool computerWin;
	char userInputForSaving;
	
	// Stores human and computer players.
	player * humanP;
	player * bot;

	// Determines who to play first in a new game.
	void determineTurn();
	int rollDie();

	const int MAX_ROW = 9;

};

