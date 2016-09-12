#include "Dice.h"



Dice::Dice(string given)
{
	front = DICE_FRONT;
	setValue(given);
}


Dice::~Dice()
{
}

string Dice::getValue() {
	return player + to_string(getTop()) + to_string(getRight());
}

void Dice::moveLeft() {
	int tmp = top;
	top = right;
	right = 7 - tmp;
}

void Dice::moveRight() {
	int tmp = top;
	top = 7 - right;
	right = tmp;
}

void Dice::moveBackward() {
	int tmp = top;
	top = 7 - front;
	front = tmp;
}

void Dice::moveForward() {
	int tmp = top;
	top = front;
	front = 7 - tmp;
}

void Dice::setValue(string val) {
	player = val.at(0);
	top = val.at(1)-'0';
	right = val.at(2) - '0';
	front = DICE_FRONT;
}

int Dice::getTop() {
	return top;
}

int Dice::getRight() {
	return right;
}