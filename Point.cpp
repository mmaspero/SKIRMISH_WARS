#include "Point.h"
#include <cmath>

Point::Point()
{
	row = col = 0;
}

Point::Point(unsigned int row, unsigned int col)
{
	this->row = row;
	this->col = col;
}

bool Point::operator==(Point p)
{
	if (p.row == row && p.col == col)
		return true;
	else
		return false;
}

bool Point::operator!=(Point p)
{
	if (p == *this)
		return false;
	else
		return true;
}

unsigned int Point::orthogonalDistanceFrom(Point p)
{
	return abs(long int(p.row) - long int(row)) + abs(long int(p.col) - long int(col));
}
