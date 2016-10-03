/************************************************************
* Name:  Sujil Maharjan                                    *
* Project : Project 1, Duell game                          *
* Class : Organization of Programming Language(CMPS 366-01)*
* Date : 10-5-2016                                         *
************************************************************/
#include "Dice.h"

/* *********************************************************************
Function Name: Dice
Purpose: Constructor.

Parameters:
	given, a string. It holds the string representation of the dice.

Return Value: none.

Local Variables: none.

Algorithm: none.

Assistance Received: none
********************************************************************* */
Dice::Dice(string given)
{
	// Find the top and right from the given string.
	top = given.at(1)-'0';
	right= given.at(2) -'0';

	// Checks if top and right are same. If yes, it means its a king.
	if (top == right) {
		setKing();
	}
	else {
		// Computes the front.
		front = computeFrontFace(top, right);
	}

	// Sets if it is a computer.
	isComputer = given.at(0) == 'C' ? true : false;

	isKilled = false;

}

/* *********************************************************************
Function Name: Dice
Purpose: Constructor. It simply creates a dice with all the information provided.

Parameters:
	isComputer, a boolean. It holds the info as to if the player is computer or not.
	topFace, an integer. It holds the top face of the die.
	frontFace, an integer. It holds the front face of the die.
	rightFace, an integer. It holds the right face of the die.

Return Value: none.

Local Variables: none.

Algorithm: none.

Assistance Received: none
********************************************************************* */
Dice::Dice(bool isComputer, int topFace, int frontFace, int rightFace) {
	this->isComputer = isComputer;

	// Checks if the die is king.
	if (topFace == frontFace) {
		setKing();
	}
	else {
		front = frontFace;
		top = topFace;
		right = rightFace;
		isKing = false;
	}

	isKilled = false;
}

/* *********************************************************************
Function Name: Dice
Purpose: Destructor.

Parameters: none.

Return Value: none.

Local Variables: none.

Algorithm: none.

Assistance Received: none
********************************************************************* */
Dice::~Dice()
{
}

/* *********************************************************************
Function Name: getValue
Purpose: To get the string representation of the die.

Parameters: none.

Return Value: Returns the string representation of the die.

Local Variables: 
	tmp, an integer. It holds the value of the top temporarily.

Algorithm: none.

Assistance Received: none
********************************************************************* */
string Dice::getValue() {
	if (isComputer) {
		return "C" + to_string(getTop()) + to_string(getRight());
	}

	return "H" + to_string(getTop()) + to_string(getRight());
}

/* *********************************************************************
Function Name: moveLeft
Purpose: To roll the die to the left. 

Parameters: none.

Return Value: none.

Local Variables: 
	tmp, an integer. It holds the value of the top temporarily.

Algorithm: 
	1. Change the top and right.

Assistance Received: none
********************************************************************* */
void Dice::moveLeft() {
	if (!isKing) {
		int tmp = top;
		top = right;
		right = 7 - tmp;
	}
}

/* *********************************************************************
Function Name: moveRight
Purpose: To roll the die to the right.

Parameters: none.

Return Value: none.

Local Variables: 
	tmp, an integer. It holds the value of the top temporarily.

Algorithm:
	1. Change the top and right.

Assistance Received: none
********************************************************************* */
void Dice::moveRight() {
	if (!isKing) {
		int tmp = top;
		top = 7 - right;
		right = tmp;
	}
}

/* *********************************************************************
Function Name: moveBackward
Purpose: To roll the die backward.

Parameters: none.

Return Value: none.

Local Variables: 
	tmp, an integer. It holds the value of the top temporarily.

Algorithm:
	1. Change the top and front of the die.

Assistance Received: none
********************************************************************* */
void Dice::moveBackward() {
	if (!isKing) {
		int tmp = top;
		top = 7 - front;
		front = tmp;
	}
}

/* *********************************************************************
Function Name: moveForward
Purpose: To roll the die forward.

Parameters: none.

Return Value: none.

Local Variables:
	tmp, an integer. It holds the value of the top temporarily.

Algorithm: none.

Assistance Received: none
********************************************************************* */
void Dice::moveForward() {
	if (!isKing) {
		int tmp = top;
		top = front;
		front = 7 - tmp;
	}
}

/* *********************************************************************
Function Name: setKing
Purpose: To set the king of the die.

Parameters: none.

Return Value: Returns true if king is successfully set.

Local Variables: none.

Algorithm: none.

Assistance Received: none
********************************************************************* */
bool Dice::setKing() {
	top = 1;
	right = 1;
	front = 1;
	isKing = true;

	return true;
}

/* *********************************************************************
Function Name: computeFrontFace
Purpose: To compute the front face of the die if top and right are given.

Parameters: 
	top, an integer. It holds the top face of the die.
	right, an integer. It holds the right face of the die.

Return Value: Returns an integer that represents the front face of the die.

Local Variables:
	roles[][], a 2d boolean array. It holds the total roll possibilities in anti-clockwise die.
	remain, an integer. It holds the opposite face of the required die.
	front, an integer. It holds the front face of the die.

Algorithm:

Assistance Received: none
********************************************************************* */
int Dice::computeFrontFace(int top, int right) {
	// It holds the total possible rolls.
	int roles[3][8] = { { 3,1,4,6,3,1,4,6 },{ 1,2,6,5,1,2,6,5 },{ 2,3,5,4,2,3,5,4 } };
	
	// It holds the remain and front face values.
	int remain = 0;
	int front = 0;

	// Checks if top is 1 and right is 2 or its equivalent opposite. Then, it finds the remaining.
	if (top == 1 || 7 - top == 1) {
		if (right == 2 || 7 - right == 2) {
			remain = 3;
		}
		else remain = 2;
	}
	// Checks if top is 2 and right is 1 or its equivalent opposite. Then, it finds the remaining.
	else if (top == 2 || 7 - top == 2) {
		if (right == 1 || 7 - right == 1) {
			remain = 3;
		}
		else remain = 1;
	}
	// Checks if top is 3 and right is 1 or its equivalent opposite. Then, it finds the remaining.
	else {
		// here top = 3
		if (right == 1 || 7 - right == 1) {
			remain = 2;
		}
		else remain = 1;
	}


	// Compute front from remain found.
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 8; j++) {
			if (roles[i][j] == top) {
				if (j + 1 < 8 && roles[i][j + 1] == right) {
					front = 7 - remain;
					break;
				}
				else if (j - 1 >= 0 && roles[i][j - 1] == right) {
					front = remain;
					break;
				}
			}
		}
	}

	// Returns the front face.
	return front;
}

/* *********************************************************************
Function Name: setKilled
Purpose: To set if the die has been killed.

Parameters: none.

Return Value: Returns true if dice can be successfullly set as killed.

Local Variables: none.

Algorithm: none.

Assistance Received: none
********************************************************************* */
bool Dice::setKilled() {
	isKilled = true;

	return true;
}