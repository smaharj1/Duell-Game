#include<iostream>
#include"Dice.h"
#include"Board.h"
#include "tournament.h"

using namespace std;

int main() {
	cout << "Hello world" << endl;

	tournament t;

	t.printWelcomeMessage();
	t.startGame();

	system("pause");
}