#pragma once
#include "contentBox.h"

class toolbox : public contentBox
{
public:
	toolbox();
	~toolbox();
private:
	virtual void drawContent();
	virtual void resizeContent();
};

