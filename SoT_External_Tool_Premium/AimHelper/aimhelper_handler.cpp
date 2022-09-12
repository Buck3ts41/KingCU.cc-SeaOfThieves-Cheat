#include "aimhelper_handler.h"


cAimHandler* AimHandler = new cAimHandler();

cAimHandler::cAimHandler()
{
}

cAimHandler::~cAimHandler()
{
}

//-> to;do
void cAimHandler::MouseMove(float x, float y)
{
	INPUT Input = { 0 };
	Input.type = INPUT_MOUSE;
	Input.mi.dx = (LONG)x;
	Input.mi.dy = (LONG)y;
	Input.mi.dwFlags = MOUSEEVENTF_MOVE;
	SendInput(1, &Input, sizeof(INPUT));
}
