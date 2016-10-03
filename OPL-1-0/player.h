/************************************************************
* Name:  Sujil Maharjan                                    *
* Project : Project 1, Duell game                          *
* Class : Organization of Programming Language(CMPS 366-01)*
* Date : 10-5-2016                                         *
************************************************************/
#pragma once
#include"Dice.h"
#include"Board.h"

using namespace std;

/*
	It is a base class for any players. It provides the functionalities such as playing and getting all the dices that the player has.
*/
class player
{
public:
	// Default constructor
	player();
	~player();

	// These are the virtual functions that allows the players to play the game and get the dices.
	virtual Dice * play(Board * board) { cout << "Base class can't play" << endl; return NULL; };
	virtual Dice ** getDices() { return NULL; }

	// It prints the move made by the player.
	static void printActivity(int row, int column, int newRow, int newCol, bool isComputer, int direction);
	
protected:
	int row, column, newRow, newCol;
	bool paths[2];

	// Checks if the move that user mentioned is inside the bounds of the board.
	bool isMoveInBound(int r, int c, int newR, int newC);

	// Constants for the limits of the board.
	const int ROW_LOW_LIMIT = 1;
	const int ROW_HIGH_LIMIT = 8;
	const int COLUMN_LOW_LIMIT = 1;
	const int COLUMN_HIGH_LIMIT = 9;

	// It holds the front face. This is initial value if you are starting a new game.
	const int FRONT_FACE = 3;

	// Enumerator that defines what algorithmic step that the player takes with heuristics.
	enum GameCondition {
		CanWin,
		CanEatKingsThreat,
		MoveKing,
		CanEatOpponent,
		PlaySafe
	};

};

