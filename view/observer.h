#pragma once
class obs
{
public:
	obs();
	~obs(); 
	virtual void update() = 0;

	bool isValid();

protected:
	bool valid;
};

