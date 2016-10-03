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

class tournament
{
public:
	tournament();
	~tournament();

	void printWelcomeMessage();
	void startGame();

	void printScore();

private:
	int totalGames;
	int humanScore;
	int computerScore;

	FileHandler * fileFunction;

	string inputFile();
};

