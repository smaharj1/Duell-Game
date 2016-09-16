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
	static string generateDice(bool isComputer);

	bool isPlayerComputer();

private:
	bool isComputer;
	int top;
	int right;
	int front;

	const int DICE_FRONT = 3;

};

