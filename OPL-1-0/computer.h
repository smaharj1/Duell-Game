#pragma once
#include"player.h"
using namespace std;

class computer : public player
{
public:
	computer();
	~computer();
	void play();

private:
	Dice * computerDices[9];
};

