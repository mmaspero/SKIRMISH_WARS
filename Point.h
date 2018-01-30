#pragma once

class Point
{
public:
	Point();
	Point(unsigned int row, unsigned int col);
	unsigned int row, col;
	bool operator==(Point p);
	bool operator!=(Point p);
	unsigned int orthogonalDistanceFrom(Point p);
};