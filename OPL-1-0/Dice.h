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

/*
	This class holds the complete functionality that a die can perform. It can roll into any directions and update the values of die accordingly.
*/
class Dice
{
public:
	// Constructor if string representation of the die is given.
	Dice(string given);

	// Constructor if 3 faces of the die is given.
	Dice(bool isComputer, int topFace, int frontFace, int rightFace);
	~Dice();

	// computes different roll actions and updates the faces of the die.
	void moveLeft();
	void moveRight();
	void moveForward();
	void moveBackward();

	// Gets the string representation of the die.
	string getValue();

	// Gets the top, right and front of the die.
	int getTop() { return top; }
	int getRight() { return right; }
	int getFront() { return front; }

	// Computes the front face of the die given top and right faces.
	static int computeFrontFace(int top, int right);

	// Returns if the player is a king and player.
	bool isPlayerKing() { return isKing; }
	bool isPlayerComputer() { return isComputer; }

	// Sets the die as king.
	bool setKing();

	// Sets the die as killed.
	bool setKilled();

private:
	// Private variables that stores all the information of the die.
	bool isComputer;
	bool isKing;
	int top;
	int right;
	int front;
	bool isKilled;
};

