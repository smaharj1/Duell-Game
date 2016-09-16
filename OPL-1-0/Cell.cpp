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