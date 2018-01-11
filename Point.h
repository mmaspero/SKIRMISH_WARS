#pragma once

class Point
{
public:
	Point();
	Point(unsigned int x, unsigned int y);
	unsigned int x, y;
	bool operator==(Point p);
	bool operator!=(Point p);
	unsigned int orthogonalDistanceFrom(Point p);
};