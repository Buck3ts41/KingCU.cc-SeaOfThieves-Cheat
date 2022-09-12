#pragma once
#include "../Core/main.h"

class cAimHandler
{
public:
	cAimHandler();
	~cAimHandler();

	void MouseMove(float x, float y);
};

extern cAimHandler* AimHandler;