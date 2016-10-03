/************************************************************
* Name:  Sujil Maharjan                                    *
* Project : Project 1, Duell game                          *
* Class : Organization of Programming Language(CMPS 366-01)*
* Date : 10-5-2016                                         *
************************************************************/
#include "player.h"



player::player()
{
}


player::~player()
{
}

/* *********************************************************************
Function Name: isMoveInBound
Purpose: To validate if the given coordinates are in bound

Parameters:
	row, an integer. It holds the row. Index starts at 1.
	column, an integer. It holds the row. Index starts at 1.
	newRow, an integer. It holds the row. Index starts at 1.
	newCol, an integer. It holds the row. Index starts at 1.

Return Value: Returns true if all of them are digits

Local Variables: none.

Algorithm: none.

Assistance Received: none
********************************************************************* */
bool player::isMoveInBound(int row, int column, int newRow, int newCol) {
	if (row < ROW_LOW_LIMIT || newRow < ROW_LOW_LIMIT || column < COLUMN_LOW_LIMIT || newCol < COLUMN_LOW_LIMIT ||
		row > ROW_HIGH_LIMIT || newRow > ROW_HIGH_LIMIT || column > COLUMN_HIGH_LIMIT || newCol > COLUMN_HIGH_LIMIT) {
		cout << "Coordinates are out of bound. Please enter again." << endl << endl;
		return false;
	}

	return true;
}

/* *********************************************************************
Function Name: printActivity
Purpose: To print the move made by the player.

Parameters:
	row, an integer. It holds the row. Index starts at 1.
	column, an integer. It holds the row. Index starts at 1.
	newRow, an integer. It holds the row. Index starts at 1.
	newCol, an integer. It holds the row. Index starts at 1.
	isComputer, a boolean. It holds if it is a computer or not.
	direction, a character. It holds the direction in which it went.

Return Value: none.

Local Variables: none.

Algorithm: none.

Assistance Received: none
********************************************************************* */
void player::printActivity(int row, int column, int newRow, int newCol, bool isComputer, int direction) {
	cout << "--------------------------------------------------------------" << endl;
	if (isComputer) {
		cout << "Computer ";
	}
	else {
		cout << "You ";
	}

	cout << "moved the dice from (" << row << "," << column << ") to (" << newRow << "," << newCol << ") taking ";

	if (direction == 'f') cout << "frontal move first";
	else cout << "lateral move first" << endl;
}
