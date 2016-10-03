/************************************************************
* Name:  Sujil Maharjan                                    *
* Project : Project 1, Duell game                          *
* Class : Organization of Programming Language(CMPS 366-01)*
* Date : 10-5-2016                                         *
************************************************************/
#pragma once
#include<iostream>
#include"game.h"

using namespace std;

/*
	This class handles a tournament by starting a new game. It also has the functionality to open a game.
*/
class tournament
{
public:
	// This is the default constructor.
	tournament();
	~tournament();

	// Prints the welcome message to the user
	void printWelcomeMessage();

	// Starts the game.
	void startGame();

	// prints the score of the array
	void printScore();

private:
	// Variables to hold the total scores.
	int totalGames;
	int humanScore;
	int computerScore;

	// It holds the file handler that will handle opening and saving in the file.
	FileHandler * fileFunction;

	// Gets the filename from the user.
	string inputFile();
};

