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

private:
	int totalGames;
	int humanScore;
	int computerScore;

	FileHandler * fileFunction;
};

