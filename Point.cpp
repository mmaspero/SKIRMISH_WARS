#include "Point.h"
#include <cmath>

Point::Point()
{
	x = y = 0;
}

Point::Point(unsigned int x, unsigned int y)
{
	this->x = x;
	this->y = y;
}

bool Point::operator==(Point p)
{
	if (p.x == x && p.y == y)
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
	return abs(long int(p.x) - long int(x)) + abs(long int(p.y) - long int(y));
}
