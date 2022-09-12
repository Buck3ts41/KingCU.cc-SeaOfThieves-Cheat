#pragma once
#include "../Core/main.h"

enum TREASURE_TYPES
{
	TREASURE_TYPE_COMMON = 0,
	TREASURE_TYPE_RARE = 1,
	TREASURE_TYPE_EPIC = 2,
	TREASURE_TYPE_MYTHICAL = 3,
	TREASURE_TYPE_LEGENDARY = 4,
	TREASURE_TYPE_MERCHANT = 5,
	TREASURE_TYPE_LORE_BOOKS = 6,
	TREASURE_TYPE_QUESTS = 7,
	TREASURE_TYPE_OTHERS = 8,
};

class cTreasuresManager
{
public:
	void treasuresUI(int treasureType, int treasureID);
};

extern cTreasuresManager* TreasuresManager;