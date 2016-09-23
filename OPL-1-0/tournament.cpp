#include "tournament.h"



tournament::tournament()
{
	totalGames = 0;
	humanScore = 0;
	computerScore = 0;

	fileFunction = new FileHandler("game.txt");
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
	game * newGame;

	bool isGameCompleted = true;

	userInput = tolower(userInput);
	while (userInput == 'y' || userInput == 'o') {
		
		if (userInput == 'y') {
			totalGames++;
			newGame = new game();
		}
		else {
			Board * tempBoard = new Board();
			bool isComputersTurn;
			fileFunction->openGame(tempBoard, isComputersTurn, computerScore, humanScore);

			newGame = new game(tempBoard, isComputersTurn);
		}
		isGameCompleted = newGame->startGame();

		if (isGameCompleted) {
			if (newGame->isComputerWinner()) {
				computerScore++;
			}
			else humanScore++;
		}
		else {
			// Game needs to be saved.
			fileFunction->saveGame(newGame->getBoard(), newGame->getIfComputerTurn(), computerScore, humanScore);

		}

		cout << "Do you want to play another game (Y/N)? :: " << endl;
		cin >> userInput;
	}
}