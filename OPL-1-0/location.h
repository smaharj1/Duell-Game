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

