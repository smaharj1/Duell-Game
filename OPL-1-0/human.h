#pragma once
#include"player.h"
using namespace std;

class human : public player
{
public:
	human();
	~human();
	void play();

private:
	Dice * humanDices[9];
};

