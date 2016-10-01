#include "computer.h"



computer::computer()
{
}

computer::computer(int keys[], int size) {
	int top = 0, right = 0, front = 0;
	int mid = size / 2;
	for (int index = 0; index < size; index++) {
		top = keys[index];
		right = 3;
		front = Dice::computeFrontFace(top, right);

		// here, right is technically front. We are considering it right to find an actual right.
		if (index == mid) {
			computerDices[index] = new Dice(true, 1, 1, 1);
		}
		else {
			computerDices[index] = new Dice(true, top, right, 7 - front);
		}

	}
}

computer::~computer()
{
}

Dice * computer::play(Board * board) {
	cout << "computer's turn to play !!!" << endl;
	return NULL;
}