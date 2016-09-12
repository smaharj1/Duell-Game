#pragma once

#include<iostream>
#include<string>

using namespace std;

class Dice
{
public:
	Dice(string given);
	~Dice();

	void moveLeft();
	void moveRight();
	void moveForward();
	void moveBackward();

	void setValue(string val);
	string getValue();

	int getTop();
	int getRight();

private:
	char player;
	int top;
	int right;
	int front;

	const int DICE_FRONT = 3;

};

