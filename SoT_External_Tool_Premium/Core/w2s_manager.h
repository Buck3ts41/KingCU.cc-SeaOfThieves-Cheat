#pragma once
#include "../Core/SOTStuff.h"
#include <codecvt>
#include <utility>
#include <locale>

class  cW2SManager
{
public:
	bool WorldToScreen(Vector3  world, Vector2* screen);

	std::string wstringToString(std::wstring wstring);
	std::wstring stringToWString(std::wstring string);
};

extern cW2SManager* W2S;
