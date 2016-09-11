#include<iostream>
#include"Dice.h"

using namespace std;

int main() {
	cout << "Hello world" << endl;

	Dice *  d = new Dice();
	d->setValue("C51");

	cout << d->getValue() << endl;
	cout << d->getTop() << "  " << d->getRight() << endl;

	system("pause");
}