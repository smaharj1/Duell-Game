#include "Dice.h"



Dice::Dice(string given)
{
	front = DICE_FRONT;
	if (given.at(1) == '1' && given.at(2) == '1') {
		setAsKing(given);
	}
	else {
		setValue(given);
	}
}


Dice::~Dice()
{
}

string Dice::getValue() {
	if (isComputer) {
		return "C" + to_string(getTop()) + to_string(getRight());
	}

	return "H" + to_string(getTop()) + to_string(getRight());
}

void Dice::moveLeft() {
	if (!isKing) {
		int tmp = top;
		top = right;
		right = 7 - tmp;
	}
}

void Dice::moveRight() {
	if (!isKing) {
		int tmp = top;
		top = 7 - right;
		right = tmp;
	}
}

void Dice::moveBackward() {
	if (!isKing) {
		int tmp = top;
		top = 7 - front;
		front = tmp;
	}
}

void Dice::moveForward() {
	if (!isKing) {
		int tmp = top;
		top = front;
		front = 7 - tmp;
	}
}

void Dice::setAsKing(string val) {
	isComputer = val.at(0) == 'C' ? true : false;
	top = 1;
	right = 1;
	front = 1;
	isKing = true;
}

bool Dice::isPlayerKing() {
	return isKing;
}

void Dice::setValue(string val) {
	isComputer = val.at(0) == 'C' ? true : false;
	top = val.at(1)-'0';
	right = val.at(2) - '0';
	front = DICE_FRONT;
	isKing = false;
}

int Dice::getTop() {
	return top;
}

int Dice::getRight() {
	return right;
}

bool Dice::isPlayerComputer() {
	return isComputer;
}