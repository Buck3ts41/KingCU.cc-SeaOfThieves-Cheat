#include "treasures_manager.h"

cTreasuresManager* TreasuresManager = new cTreasuresManager();

void cTreasuresManager::treasuresUI(int treasureType, int treasureID)
{
	switch (treasureType)
	{
	case TREASURE_TYPE_COMMON:
	{
		switch (treasureID)
		{
		case 1:
		{
			ImGui::Text("test");
		}
		break;
		
		default:
			break;
		}
	}
	break;
	case TREASURE_TYPE_RARE:
	case TREASURE_TYPE_EPIC:
	case TREASURE_TYPE_MYTHICAL:
	case TREASURE_TYPE_LEGENDARY:
	case TREASURE_TYPE_MERCHANT:
	case TREASURE_TYPE_LORE_BOOKS:
	case TREASURE_TYPE_QUESTS:
	case TREASURE_TYPE_OTHERS:
		break;
	}
}
