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

	int computeFrontFace(int top, int right);
	void setAsKing(string val);

	bool isPlayerKing();

	bool isPlayerComputer();

private:
	bool isComputer;
	bool isKing;
	int top;
	int right;
	int front;

	const int DICE_FRONT = 3;

};

