#include "data_manager.h"

cDataManager* DataManager = new cDataManager();

using namespace std;

bool cDataManager::IsA(int objectType, string objectName)
{
	switch (objectType)
	{
	case PLAYER:
		for (int i = 0; i < this->player_objects.size(); i++)
		{
			if (objectName.find(player_objects[i]) != string::npos)
				return true;
		}
		break;
		
	case SHIP:
		break;

	case CHEST:
		for (int i = 0; i < this->chest_objects.size(); i++)
		{
			if (objectName.find(chest_objects[i]) != string::npos)
				return true;
		}
		break;
	}
	return false;
}

bool cDataManager::IsRarity(int objectRarity, string objectName)
{
	switch (objectRarity)
	{
	case COMMON:
	case RARE:
	case EPIC:
	case MYTHICAL:
	case LEGENDARY:
	case MERCHANT:
	case LORE_BOOK:
	case QUEST_ITEM:
	case OTHER:
		break;
	}
	return false;
}
