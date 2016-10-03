/************************************************************
* Name:  Sujil Maharjan                                    *
* Project : Project 1, Duell game                          *
* Class : Organization of Programming Language(CMPS 366-01)*
* Date : 10-5-2016                                         *
************************************************************/
#pragma once
class location
{
public:
	location();
	location(int r, int c);
	~location();

	int getRow() { return row; }
	int getColumn() { return col; }

private:
	int row;
	int col;
};

