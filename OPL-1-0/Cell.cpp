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

bool Cell::addDice(Dice * givenDice) {
	if (dice == NULL) {
		dice = givenDice;
		return true;
	}

	return false;
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