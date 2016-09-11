#include "Dice.h"



Dice::Dice()
{
}


Dice::~Dice()
{
}

string Dice::getValue() {
	return diceValue;
}

void Dice::moveLeft() {

}

void Dice::moveRight() {

}

void Dice::moveBackward() {

}

void Dice::moveForward() {

}

void Dice::setValue(string val) {
	diceValue = val;
	top = val.at(topIndex)-'0';
	right = val.at(rightIndex) - '0';
}

int Dice::getTop() {
	return top;
}

int Dice::getRight() {
	return right;
}