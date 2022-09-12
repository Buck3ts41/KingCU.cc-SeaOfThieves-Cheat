#pragma once
#include "../Core/main.h"
#include <vector>

using namespace std;

enum OBJECT_TYPE
{
	PLAYER = 0,
	SHIP = 1,
	CHEST = 2,
	SKULL = 3,
};

enum OBJECT_RARITY
{
	COMMON = 0,
	RARE = 1,
	EPIC = 2,
	MYTHICAL = 3,
	LEGENDARY = 4,
	MERCHANT = 5,
	LORE_BOOK = 6,
	QUEST_ITEM = 7,
	OTHER = 8,
};

class cDataManager
{
public:
	bool IsA(int objectType, std::string objectName);
	bool IsRarity(int objectRarity, string objectName);

	vector<string> player_objects = { "BP_PlayerPirate_C" };
	vector<string> chest_objects = { "BP_AmmoChest_C" };

};

extern cDataManager* DataManager;