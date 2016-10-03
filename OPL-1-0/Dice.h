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

	string getValue();

	int getTop() { return top; }
	int getRight() { return right; }
	int getFront() { return front; }

	static int computeFrontFace(int top, int right);

	bool isPlayerKing() { return isKing; }
	bool isPlayerComputer() { return isComputer; }
	bool setKing();

	bool setKilled();

private:
	bool isComputer;
	bool isKing;
	int top;
	int right;
	int front;
	bool isKilled;
};

