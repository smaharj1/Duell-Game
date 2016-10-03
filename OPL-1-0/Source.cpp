/************************************************************
* Name:  Sujil Maharjan                                    *
* Project : Project 1, Duell game                          *
* Class : Organization of Programming Language(CMPS 366-01)*
* Date : 10-5-2016                                         *
************************************************************/
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