/************************************************************
* Name:  Sujil Maharjan                                    *
* Project : Project 1, Duell game                          *
* Class : Organization of Programming Language(CMPS 366-01)*
* Date : 10-5-2016                                         *
************************************************************/
#include "location.h"


/* *********************************************************************
Function Name: location
Purpose: Constructor.

Parameters: 
	givenRow, an integer. It holds the row number.
	givenCol, an integer. It holds the column number.

Return Value:  none.

Local Variables: none.

Algorithm: none.

Assistance Received: none
********************************************************************* */
location::location(int givenRow, int givenCol)
{
	row = givenRow;
	col = givenCol;
}


location::~location()
{
}
