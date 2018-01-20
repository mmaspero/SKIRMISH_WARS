#pragma once
#include "Move.h"

class Attack : public Action {
public:
	Attack(Point target, Point whereFrom, unsigned int mps = 0);
	Point target;
};