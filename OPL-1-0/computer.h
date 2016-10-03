/************************************************************
* Name:  Sujil Maharjan                                    *
* Project : Project 1, Duell game                          *
* Class : Organization of Programming Language(CMPS 366-01)*
* Date : 10-5-2016                                         *
************************************************************/
#pragma once
#include"player.h"
#include "Board.h"
#include"algorithm.h"
using namespace std;

/*
	This class is inherited from player class which works for a computer and provides various functionalities to play the game.
*/
class computer : public player
{
public:
	// Constructor if keys and size are given. This is if we are starting a new game.
	computer(int keys[], int size);

	// Constructor if we are loading the game from a text file.
	computer(Board * board);
	~computer();

	// Plays the game and returns a die if the movement results in eating any die.
	Dice * play(Board * board);

	// Prints the move.
	void printMove(Dice * givenDice, int row, int column, int newRow, int newCol, GameCondition condition);
	
	// Returns the die.
	Dice ** getDices() { return computerDices; }

private:
	Dice * computerDices[9];
};

