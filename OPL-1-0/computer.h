#pragma once
#include"player.h"
#include "Board.h"
using namespace std;

class computer : public player
{
public:
	computer();
	computer(int keys[], int size);
	~computer();
	Dice * play(Board * board);

private:
	Dice * computerDices[9];
};

