/************************************************************
* Name:  Sujil Maharjan                                    *
* Project : Project 1, Duell game                          *
* Class : Organization of Programming Language(CMPS 366-01)*
* Date : 10-5-2016                                         *
************************************************************/
#include "Cell.h"



Cell::Cell()
{
	dice = NULL;
}

Cell::Cell(Dice * d) {
	dice = d;
}
Cell::~Cell()
{
}

void Cell::addDice(Dice * givenDice) {
	dice = givenDice;
}

bool Cell::isEmpty() {
	return dice == NULL;
}

Dice * Cell::getDice() {
	return dice;
}

void Cell::removeDice() {
	dice = NULL;
}