/************************************************************
* Name:  Sujil Maharjan                                    *
* Project : Project 1, Duell game                          *
* Class : Organization of Programming Language(CMPS 366-01)*
* Date : 10-5-2016                                         *
************************************************************/
#pragma once

#include<iostream>
#include<string>

using namespace std;

class Dice
{
public:
	Dice(string given);
	Dice(bool isComputer, int topFace, int frontFace, int rightFace);
	~Dice();

	void moveLeft();
	void moveRight();
	void moveForward();
	void moveBackward();

	void setValue(string val);
	string getValue();

	int getTop();
	int getRight();

	static int computeFrontFace(int top, int right);
	void setAsKing(string val);

	bool isPlayerKing();

	bool isPlayerComputer();
	bool setKing();

	bool setKilled();

private:
	bool isComputer;
	bool isKing;
	int top;
	int right;
	int front;
	bool isKilled;

	const int DICE_FRONT = 3;

};

