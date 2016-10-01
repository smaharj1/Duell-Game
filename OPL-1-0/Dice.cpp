#include "Dice.h"

Dice::Dice(string given)
{
	top = given.at(1)-'0';
	right= given.at(2) -'0';

	if (top == right) {
		setKing();
	}
	else {
		front = computeFrontFace(top, right);
	}

	isComputer = given.at(0) == 'C' ? true : false;

	isKilled = false;

}

Dice::Dice(bool isComputer, int topFace, int frontFace, int rightFace) {
	this->isComputer = isComputer;
	if (topFace == frontFace) {
		setKing();
	}
	else {
		front = frontFace;
		top = topFace;
		right = rightFace;
		isKing = false;
	}

	isKilled = false;

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


bool Dice::setKing() {
	top = 1;
	right = 1;
	front = 1;
	isKing = true;

	return true;
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

int Dice::computeFrontFace(int top, int right) {
	int roles[3][8] = { { 3,1,4,6,3,1,4,6 },{ 1,2,6,5,1,2,6,5 },{ 2,3,5,4,2,3,5,4 } };
	int remain = 0;
	int front = 0;

	if (top == 1 || 7 - top == 1) {
		if (right == 2 || 7 - right == 2) {
			remain = 3;
		}
		else remain = 2;
	}
	else if (top == 2 || 7 - top == 2) {
		if (right == 1 || 7 - right == 1) {
			remain = 3;
		}
		else remain = 1;
	}
	else {
		// here top = 3
		if (right == 1 || 7 - right == 1) {
			remain = 2;
		}
		else remain = 1;
	}


	// compute front
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 8; j++) {
			if (roles[i][j] == top) {
				if (j + 1 < 8 && roles[i][j + 1] == right) {
					front = 7 - remain;
					break;
				}
				else if (j - 1 >= 0 && roles[i][j - 1] == right) {
					front = remain;
					break;
				}
			}
		}
	}

	return front;
}

bool Dice::setKilled() {
	isKilled = true;

	return true;
}