#pragma once
#include"player.h"
#include"Board.h"
using namespace std;

class human : public player
{
public:
	human();
	~human();
	Dice * play(Board * board);

private:
	Dice * humanDices[9];
};

