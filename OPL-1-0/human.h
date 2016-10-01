#pragma once
#include"player.h"
#include"Board.h"
using namespace std;

class human : public player
{
public:
	human();
	human(int keys[], int size);
	human(Board * board);
	~human();
	Dice * play(Board * board);

	Dice ** getDices() { return humanDices; }



private:
	Dice * humanDices[9];

	bool validValues(char row, char col, char newRow, char newCol);
};

