#pragma once
class observer
{
public:
	observer();
	~observer(); 
	virtual void update() = 0;
};

