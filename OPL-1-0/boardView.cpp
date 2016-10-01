#include "boardView.h"



BoardView::BoardView()
{
}


BoardView::~BoardView()
{
}

void BoardView::printBoard() {
	cout << endl << "-------------------------------------x----------------------------------" << endl;
	for (int i = 0; i <= board->getTotalRows(); i++) {
		if (i == board->getTotalRows()) {
			cout << "   ";
			for (int j = 0; j <= board->getTotalColumns(); j++) {
				if (j != 0) {
					cout << "  " << j << "  ";
				}
			}
			cout << endl;
		}
		else {
			for (int j = -1; j < board->getTotalColumns(); j++) {
				if (j < 0) {
					cout << 8 - i << "  ";
					continue;
				}

				if (board->getCell(i, j)->getDice() != NULL) {
					cout << board->getCell(i, j)->getDice()->getValue() << "  ";
				}
				else {
					cout << "  0  ";
				}
			}
			cout << endl;
		}
	}
	cout << endl << "-------------------------------------x----------------------------------" << endl;
	
}