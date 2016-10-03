/************************************************************
* Name:  Sujil Maharjan                                    *
* Project : Project 1, Duell game                          *
* Class : Organization of Programming Language(CMPS 366-01)*
* Date : 10-5-2016                                         *
************************************************************/
#include "boardView.h"


/* *********************************************************************
Function Name: BoardView
Purpose: A default constructor.

Parameters: none.

Return Value: none.

Local Variables: none.

Algorithm: none.

Assistance Received: none
********************************************************************* */
BoardView::BoardView()
{
	board = NULL;
}

/* *********************************************************************
Function Name: BoardView
Purpose: Destructor for the class.

Parameters: none.

Return Value: none.

Local Variables: none.

Algorithm: none.

Assistance Received: none
********************************************************************* */
BoardView::~BoardView()
{
}

/* *********************************************************************
Function Name: printBoard
Purpose: To print the given board

Parameters: none.

Return Value: none.

Local Variables: none.

Algorithm: 
	1. Loops through each cell of the board and prints the dice on it.

Assistance Received: none
********************************************************************* */
void BoardView::printBoard() {
	cout << endl << "-------------------------------------x----------------------------------" << endl;
	for (int i = 0; i <= board->getTotalRows(); i++) {
		if (i == board->getTotalRows()) {
			cout << "   ";
			for (int j = 0; j <= board->getTotalColumns(); j++) {
				if (j != 0) {
					cout << "  " << j << "  ";
				}
			}
			cout << endl;
		}
		else {
			for (int j = -1; j < board->getTotalColumns(); j++) {
				if (j < 0) {
					cout << 8 - i << "  ";
					continue;
				}

				if (board->getCell(i, j)->getDice() != NULL) {
					cout << board->getCell(i, j)->getDice()->getValue() << "  ";
				}
				else {
					cout << "  0  ";
				}
			}
			cout << endl;
		}
	}
	cout << endl << "-------------------------------------x----------------------------------" << endl;
}

/* *********************************************************************
Function Name: setBoard
Purpose: To set the board.

Parameters: 
	givenBoard, a pointer to the Board. It holds the pointer to the Board class.

Return Value: Returns true if it successfully sets the board.

Local Variables: none.

Algorithm: none.

Assistance Received: none
********************************************************************* */
bool BoardView::setBoard(Board * givenBoard) {
	// If board is not null, return that the new board cannot be set.
	if (board != NULL) {
		return false;
	}

	// Set the value of the board.
	board = givenBoard;

	return true;
}