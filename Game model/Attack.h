#pragma once
#include "Move.h"

class Attack : public Move {
public:
	Attack(Point target, Point whereFrom, unsigned int mps = 0);
	Point target;
};