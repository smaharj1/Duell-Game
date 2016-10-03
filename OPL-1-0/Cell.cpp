/************************************************************
* Name:  Sujil Maharjan                                    *
* Project : Project 1, Duell game                          *
* Class : Organization of Programming Language(CMPS 366-01)*
* Date : 10-5-2016                                         *
************************************************************/
#include "Cell.h"

/* *********************************************************************
Function Name: Cell
Purpose: Default constructor

Parameters: none.

Return Value: none.

Local Variables: none.

Algorithm: none.

Assistance Received: none
********************************************************************* */
Cell::Cell()
{
	dice = NULL;
}
/* *********************************************************************
Function Name: Cell
Purpose: Constructor.

Parameters:
	givenDice, a pointer to the dice. It holds the pointer to the dice.

Return Value: none.

Local Variables: none.

Algorithm: none.

Assistance Received: none
********************************************************************* */
Cell::Cell(Dice * givenDice) {
	dice = givenDice;
}

/* *********************************************************************
Function Name: ~Cell
Purpose: Destructor.

Parameters: none.

Return Value: none.

Local Variables: none.

Algorithm: none.

Assistance Received: none
********************************************************************* */
Cell::~Cell()
{
}

/* *********************************************************************
Function Name: addDice
Purpose: To add dice to the given cell. It ignores even if the cell already 
	has the dice in it.

Parameters: 
	givenDice, a pointer. It holds the pointer to the dice.

Return Value: Returns true if dice is added.

Local Variables: none.

Algorithm: none.

Assistance Received: none
********************************************************************* */
bool Cell::setDice(Dice * givenDice) {
	dice = givenDice;

	return true;
}

/* *********************************************************************
Function Name: isEmpty
Purpose: To check if the chosen cell is empty or it contains a dice.

Parameters: none.

Return Value: Returns true if the cell does not contain any dice.

Local Variables: none.

Algorithm: none.

Assistance Received: none
********************************************************************* */
bool Cell::isEmpty() {
	return dice == NULL;
}

/* *********************************************************************
Function Name: getDice
Purpose: To return dice in the cell.

Parameters: none.

Return Value: Returns the pointer to the dice of the cell.

Local Variables: none.

Algorithm: none.

Assistance Received: none
********************************************************************* */
Dice * Cell::getDice() {
	return dice;
}

/* *********************************************************************
Function Name: removeDice
Purpose: To remove the dice from the cell.

Parameters: none.

Return Value: none.

Local Variables: none.

Algorithm: none.

Assistance Received: none
********************************************************************* */
void Cell::removeDice() {
	dice = NULL;
}
