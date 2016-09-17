#include "boardView.h"



BoardView::BoardView()
{
}


BoardView::~BoardView()
{
}

void BoardView::printBoard() {
	for (int i = 0; i < board->getTotalRows(); i++) {
		for (int j = 0; j < board->getTotalColumns(); j++) {
			if (board->getCell(i,j)->getDice() != NULL) {
				cout << board->getCell(i, j)->getDice()->getValue() << "  ";
			}
			else {
				cout << "  0  ";
			}
		}
		cout << endl;
	}
	
}