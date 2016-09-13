#include<iostream>
#include"Dice.h"
#include"Board.h"

using namespace std;

int main() {
	cout << "Hello world" << endl;

	Dice *  d = new Dice("C51");
	d->setValue("C51");

	Board b = Board();

	b.printBoard();

	cout << endl << endl;

	b.move(8, 1, 2, 0);
	b.printBoard();
	
	system("pause");
}