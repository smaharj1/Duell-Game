#pragma once
#include"Dice.h"
#include"Board.h"

using namespace std;

class player
{
public:
	player();
	~player();
	virtual Dice * play(Board * board) { cout << "Base class can't play" << endl; return NULL; };
	virtual Dice ** getDices() { return NULL; }

	int getRow();
	int getColumn();
	int getNewRow();
	int getNewCol();
protected:
	int totalWins;

	int row, column, newRow, newCol;
	bool paths[2];

	int isMoveInBound(int r, int c, int newR, int newC);



	const int ROW_LOW_LIMIT = 1;
	const int ROW_HIGH_LIMIT = 8;
	const int COLUMN_LOW_LIMIT = 1;
	const int COLUMN_HIGH_LIMIT = 9;

};

