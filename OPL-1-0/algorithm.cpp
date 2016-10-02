#include"algorithm.h"

algorithm::algorithm()
{
}

algorithm::algorithm(Board * board, bool isComputer) {
	refreshPlayers(board, isComputer);
}
bool algorithm::goDefence(Board * board, bool isComputer) {
	// Check for imminent threat by other player.
	if (kingInThreat(board)) {
		// Move the king if there is an imminent threat
		if (canEatThreat(board) ) {
			return true;
		}
		else return false;
	}
	// If there is no threat, then see the king can be surrounded for obstruction.

	// If both of these are not the scenarios, return false

	return false;
}

bool algorithm::canMoveKing(Board * board, bool isComputer) {
	treeNode * playerKing = getCurrentPlayersKing();
	
	int front = playerKing->getRow()+1;
	int back = playerKing->getRow() - 1;
	int left = playerKing->getColumn() + 1;
	int right = playerKing->getColumn() - 1;

	suggestedMove = NULL;
	suggestedNewLocation = NULL;

	// For frontal move of king.
	if (front < board->getTotalRows() && front >= 0) {
		if (board->isLegalAlgo(playerKing->getRow(), playerKing->getColumn(), front, playerKing->getColumn(), isComputer)) {
			suggestedMove = playerKing;
			suggestedNewLocation = new location(front, playerKing->getColumn());
			return true;
		}
	}
	
	if (back < board->getTotalRows() && back >= 0) {
		if (board->isLegalAlgo(playerKing->getRow(), playerKing->getColumn(), back, playerKing->getColumn(), isComputer)) {
			suggestedMove = playerKing;
			suggestedNewLocation = new location(back, playerKing->getColumn());
			return true;
		}
	}

	if (left < board->getTotalColumns() && left >= 0) {
		if (board->isLegalAlgo(playerKing->getRow(), playerKing->getColumn(), playerKing->getRow(), left, isComputer)) {
			suggestedMove = playerKing;
			suggestedNewLocation = new location(playerKing->getRow(), left);
			return true;
		}
	}

	if (right < board->getTotalColumns() && right>= 0) {
		if (board->isLegalAlgo(playerKing->getRow(), playerKing->getColumn(), playerKing->getRow(), right, isComputer)) {
			suggestedMove = playerKing;
			suggestedNewLocation = new location(playerKing->getRow(), right);
			return true;
		}
	}

	return false;
}

treeNode * algorithm::getCurrentPlayersKing() {
	for (int i = 0; i < currentPlayer.size(); i++) {
		if (currentPlayer[i]->getDice()->isPlayerKing()) {
			return currentPlayer[i];
		}
	}

	return NULL;
}

treeNode * algorithm::getOpponentsKing() {

	for (int i = 0; i < opponentPlayer.size(); i++) {
		if (opponentPlayer[i]->getDice()->isPlayerKing()) {
			return opponentPlayer[i];
		}
	}

	return NULL;
}

bool algorithm::canEatThreat(Board * board) {
	if (threateningNode == NULL) {
		return false;
	}

	// At this point, threatening node is not null.
	// Loop through each dice of players and see if you can eat threatening node.
	for (int index = 0; index < currentPlayer.size(); index++) {
		treeNode * tempNode = currentPlayer[index];
		if (board->checkPathForAlgo(tempNode->getRow(), tempNode->getColumn(), threateningNode->getRow(), threateningNode->getColumn(), true)) {
			suggestedMove = tempNode;
			suggestedNewLocation = threateningNode->getLocation();
			return true;
		}
	}

	suggestedMove = NULL;
	suggestedNewLocation = NULL;

	return false;
}

bool algorithm::kingInThreat(Board * board) {
	treeNode * playerKing;

	for (int i = 0; i < currentPlayer.size(); i++) {
		if (currentPlayer[i]->getDice()->isPlayerKing()) {
			playerKing = currentPlayer[i];
		}
	}

	bool tempArray[2];
	tempArray[0] = true;
	tempArray[1] = true;

	// Check if each of opponent players can legally move to king's location
	for (int i = 0; i < opponentPlayer.size(); i++) {
		//cout << "Opponent's dices: " << opponentPlayer[i]->getDice()->getValue() << endl;
		treeNode * tempNode = opponentPlayer[i];
		if (board->checkPathForAlgo(tempNode->getRow() , tempNode->getColumn(), playerKing->getRow(), playerKing->getColumn() , true)) {
			cout << "King is in imminent threat by " << opponentPlayer[i]->getDice()->getValue() << endl;
			threateningNode = opponentPlayer[i];
			return true;
		}
	}
	
	threateningNode = NULL;
	return false;
}

void algorithm::refreshPlayers(Board * board, bool isComputer) {
	opponentPlayer.clear();
	currentPlayer.clear();

	for (int row = 0; row < board->getTotalRows(); row++) {
		for (int col = 0; col < board->getTotalColumns(); col++) {
			if (!board->getCell(row, col)->isEmpty()) {
				Dice * d = board->getCell(row, col)->getDice();
				
				if (d->isPlayerComputer() != isComputer) {
					opponentPlayer.push_back(new treeNode(d, row, col));
				}
				else {
					currentPlayer.push_back(new treeNode(d, row, col));
				}
			}
		}
	}
}