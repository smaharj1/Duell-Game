#pragma once

#include<iostream>
#include<string>

using namespace std;

class Dice
{
public:
	Dice();
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
	string diceValue;
	int top;
	int right;

	const int topIndex = 1;
	const int rightIndex = 2;
};

