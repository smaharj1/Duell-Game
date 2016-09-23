#include<iostream>
#include"Dice.h"
#include"Board.h"
#include "tournament.h"
#include<fstream>

using namespace std;

int main() {
	cout << "Hello world" << endl;

	tournament t;

	t.printWelcomeMessage();
	t.startGame();


	system("pause");
}