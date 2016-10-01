#pragma once
#include"player.h"
#include "Board.h"
using namespace std;

class computer : public player
{
public:
	computer();
	~computer();
	void play(Board * board);

private:
	Dice * computerDices[9];
};

