#include "tournament.h"



tournament::tournament()
{
	totalGames = 0;
	humanScore = 0;
	computerScore = 0;
}


tournament::~tournament()
{
}

void tournament::printWelcomeMessage() {
	cout << "Welcome to the wonderful game of Duell" << endl;
	cout << "We are very delighted that you chose to play this game" << endl;
}

void tournament::startGame() {
	char userInput;
	cout << "Do you want to start a new game (Y/N)? :: " << endl;
	cin >> userInput;
	game newGame;

	while (userInput == 'Y' || userInput == 'y') {
		totalGames++;
		newGame = game();
		newGame.startGame();

		if (newGame.isComputerWinner()) {
			computerScore++;		
		}
		else humanScore++;

		cout << "Do you want to play another game (Y/N)? :: " << endl;
		cin >> userInput;
	}
}