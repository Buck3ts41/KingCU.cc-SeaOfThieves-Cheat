#include "drawing_manager.h"

cDrawingManager* DrawingManager = new cDrawingManager();

using namespace std;

string cDrawingManager::getNameFromIDmem(int ID)
{
	try
	{
		DWORD_PTR fNamePtr = MemoryManager->Read<uintptr_t>(GLOBAL_DEFINITION::GNames + int(ID / 0x4000) * 0x8);
		DWORD_PTR fName = MemoryManager->Read<uintptr_t>(fNamePtr + 0x8 * int(ID % 0x4000));
		return MemoryManager->Read<text>(fName + 0x10).word;
	}
	catch (int e)
	{
		return string("");
	}
}


string cDrawingManager::getNameFromIDmap(int ID)
{
	auto it = Names.find(ID);


	if (it == Names.end())
		return "";
	else
		return it->second;
}

double _clockToMilliseconds(clock_t ticks)
{
	return (ticks / (double)CLOCKS_PER_SEC) * 1000.0;
}

double _elapsedTime(clock_t start, clock_t end)
{
	return (end - start);
}

Vector2 RotatePoint(Vector2 pointToRotate, Vector2 centerPoint, float angle, bool angleInRadians = false)
{
	if (!angleInRadians)
		angle = static_cast<float>(angle * (PI / 180.f));
	float cosTheta = static_cast<float>(cos(angle));
	float sinTheta = static_cast<float>(sin(angle));
	Vector2 returnVec = Vector2(cosTheta * (pointToRotate.x - centerPoint.x) - sinTheta * (pointToRotate.y - centerPoint.y), sinTheta * (pointToRotate.x - centerPoint.x) + cosTheta * (pointToRotate.y - centerPoint.y)
	);
	returnVec += centerPoint;
	return returnVec;
}

void objectsDataShare()
{
	while (true)
	{
		vector<ActorsList> tempActorsData;

		auto gameWorld = MemoryManager->Read<cUWorld>(MemoryManager->Read<uintptr_t>(GLOBAL_DEFINITION::UWorld));
		auto LP = gameWorld.GetGameInstance().GetLocalPlayer();
		auto LPController = LP.GetPlayerController();
		auto LPCameraManager = LPController.GetCameraManager();

		SOT->localPlayer.name = W2S->wstringToString(LPController.GetActor().GetPlayerState().GetName());

		SOT->localPlayer.position = LPController.GetActor().GetRootComponent().GetPosition();

		SOT->localCamera.fov = LPCameraManager.GetCameraFOV();
		SOT->localCamera.angles = LPCameraManager.GetCameraRotation();
		SOT->localCamera.position = LPCameraManager.GetCameraPosition();

		auto worldLevel = gameWorld.GetLevel();
		auto worldActors = worldLevel.GetActors();

		if (!worldActors.IsValid() || worldActors.Length() == 0)
			return;

		for (int i = 0; i < worldActors.Length(); ++i)
		{
			auto objectActor = *reinterpret_cast<AActor*>(&worldActors[i]);

			if (objectActor == LPController.GetActor())
			{
				auto objectCharacter = *reinterpret_cast<ACharacter*>(&worldActors[i]);

				ActorsList Actor{};
				Actor.IsLocalPlayer = true;
				Actor.oxygenLevel = objectCharacter.GetDrowningComponent().GetOxygenLevel();
				tempActorsData.push_back(Actor);

				continue;
			}

			auto objectID = objectActor.GetID();
			auto objectName = DrawingManager->getNameFromIDmem(objectID);
			auto objectPosition = objectActor.GetRootComponent().GetPosition();
			auto objectDistance = SOT->localCamera.position.DistTo(objectPosition) / 100.00f;

			if (objectName.find("MapTable_C") != std::string::npos)
			{
				auto Table = *reinterpret_cast<AMapTable*>(&worldActors[i]);
				auto Ships = Table.GetTrackedShips();

				if (Ships.IsValid())
				{
					for (int p = 0; p < Ships.Length(); ++p)
					{
						auto Ship = Ships[p];

						for (int c = 0; c < 6; ++c)
						{
							if (Ship.GetCrewId() == SOT->Ships[c].crewID)
							{
								int id = Ship.GetUObject().nameId;
								auto temp = DrawingManager->getNameFromIDmem(id);
								auto tempName = DrawingManager->getNameFromIDmem(Ship.GetUObject().nameId);
								SOT->Ships[c].type = DrawingManager->getNameFromIDmem(Ship.GetUObject().nameId);
								cout << id << " - " << temp << " - " << tempName << "\n" << endl;
							}
						}
					}
				}
			}

			//-> ASSIGN PLAYERS TO CREWS
			else if (objectName.find("CrewService") != string::npos)
			{
				DrawingManager->Crews.clear();

				Team tempTeam;
				TeamMate tempPlayers;
				auto crewService = *reinterpret_cast<ACrewService*>(&worldActors[i]);;
				auto crews = crewService.GetCrews();
				if (!crews.IsValid())
					continue;

				for (int c = 0; c < crews.Length(); ++c)
				{
					auto players = crews[c].GetPlayers();
					if (!players.IsValid())
						continue;

					tempTeam.teamName = crews[c].GetShipType();
					
					/*
					-> Arena Team Names
					
					to;do
					*/

					//if (SOT->Ships[c].type.find("azure") != std::string::npos)
					//	printf("azure\n");
					//else if (SOT->Ships[c].type.find("regal") != std::string::npos)
					//	printf("regal\n");
					//else if (SOT->Ships[c].type.find("lucky") != std::string::npos)
					//	printf("lucky\n");
					//else if (SOT->Ships[c].type.find("flaming") != std::string::npos)
					//	printf("flaming\n");
					//else if (SOT->Ships[c].type.find("golden") != std::string::npos)
					//	printf("golden\n");
					//else
					//	printf("white\n");

					SOT->Ships[c].crewID = crews[c].GetCrewID();

					for (int p = 0; p < players.Length(); ++p)
					{
						tempPlayers.PlayerName = W2S->wstringToString(players[p].GetName());
						if (tempPlayers.PlayerName == SOT->localPlayer.name)
							SOT->localPlayer.crewID = crews[c].GetCrewID();

						SOT->Pirates[(c * 4) + p].crewID = crews[c].GetCrewID();
						SOT->Pirates[(c * 4) + p].name = tempPlayers.PlayerName;

						tempTeam.Players.push_back(tempPlayers);
					}
					DrawingManager->Crews.push_back(tempTeam);
					tempTeam.Players.clear();
				}
			}

			//-> PLAYERS
			else if (objectName.find("BP_PlayerPirate_C") != string::npos)
			{
				ActorsList Actor{};

				Actor.objectID = objectID;
				Actor.objectName = objectName;
				Actor.objectPosition = objectPosition;
				Actor.objectDistance = objectDistance;

				Actor.pirateName = W2S->wstringToString(objectActor.GetPlayerState().GetName());
				Actor.pirateHealth = objectActor.GetHealthComponent().GetHealth();
				Actor.pirateMaxHealth = objectActor.GetHealthComponent().GetMaxHealth();

				string itemName = W2S->wstringToString(objectActor.GetWieldedItemComponent().GetWieldedItem().GetItemInfo().GetItemDesc().GetName());
				if (itemName == "")
					Actor.pirateItemName = "NONE";
				else
					Actor.pirateItemName = itemName;

				tempActorsData.push_back(Actor);
			}

			//-> SHIPS
			else if (objectName.find("BP_SmallShipTemplate_C") != string::npos
				|| objectName.find("BP_SmallShipNetProxy") != string::npos
				|| objectName.find("BP_MediumShipTemplate_C") != string::npos
				|| objectName.find("BP_MediumShipNetProxy") != string::npos
				|| objectName.find("BP_LargeShipTemplate_C") != string::npos
				|| objectName.find("BP_LargeShipNetProxy") != string::npos
				|| objectName.find("BP_Rowboat_C") != string::npos
				|| objectName.find("BP_RowboatRowingSeat_C") != string::npos
				|| objectName.find("BP_AISmallShipTemplate_C") != string::npos
				|| objectName.find("BP_AISmallShipNetProxy_C") != string::npos
				|| objectName.find("BP_AILargeShipTemplate_C") != string::npos
				|| objectName.find("BP_AILargeShipNetProxy_C") != string::npos
				|| objectName.find("BP_Rowboat_WithFrontHarpoon_C") != string::npos)
			{
				ActorsList Actor{};

				auto objectShip = *reinterpret_cast<AShip*>(&worldActors[i]);
				FGuid crewID = objectShip.GetCrewOwnershipComponent().GetCrewId();

				if (SOT->localPlayer.crewID == crewID)
					Actor.IsShipAllied = true;
				else
					Actor.IsShipAllied = false;

				Actor.objectID = objectID;
				Actor.objectName = objectName;
				Actor.objectPosition = objectPosition;
				Actor.objectDistance = objectDistance;

				tempActorsData.push_back(Actor);
			}

			//-> ITEMS/CHESTS INFO
			else if (objectName.find("Proxy") != string::npos && objectName.find("NetProxy") == string::npos)
			{
				ActorsList Actor{};

				Actor.objectID = objectID;
				Actor.objectName = objectName;
				Actor.objectPosition = objectPosition;
				Actor.objectDistance = objectDistance;

				auto getTreasure = *reinterpret_cast<AItemProxy*>(&worldActors[i]);
				int treasureType = getTreasure.GetBootyItemInfo().GetBootyType();

				if (treasureType > EBootyTypes::EBootyTypes__EBootyTypes_MAX || treasureType < 1)
					continue;

				Actor.treasureRarity = DrawingManager->getNameFromIDmem(getTreasure.GetBootyItemInfo().GetRareityId());

				wstring tempTreasureName = getTreasure.GetBootyItemInfo().GetItemDesc().GetName();
				transform(tempTreasureName.begin(), tempTreasureName.end(), tempTreasureName.begin(), ::toupper);
				Actor.treasureName = tempTreasureName;

				tempActorsData.push_back(Actor);
			}
			
			//-> DAMAGE ZONES
			else if (objectName.find("DamageZone") != string::npos)
			{
			ActorsList Actor{};

			Actor.objectID = objectID;
			Actor.objectName = objectName;
			Actor.objectPosition = objectPosition;
			Actor.objectDistance = objectDistance;

			tempActorsData.push_back(Actor);
			}

			//-> OBJECTS
			else if (objectName.find("BP_AmmoChest_C") != string::npos)
			{
				ActorsList Actor{};

				Actor.objectID = objectID;
				Actor.objectName = objectName;
				Actor.objectPosition = objectPosition;
				Actor.objectDistance = objectDistance;

				tempActorsData.push_back(Actor);
			}

			else if (objectName.find("BP_IslandStorageBarrel") != string::npos)
			{
				ActorsList Actor{};

				Actor.objectID = objectID;
				Actor.objectName = objectName;
				Actor.objectPosition = objectPosition;
				Actor.objectDistance = objectDistance;

				tempActorsData.push_back(Actor);
			}

			else if (objectName.find("BP_Cannon_C") != string::npos)
			{
				ActorsList Actor{};

				auto Cannon = *reinterpret_cast<ACannon*>(&worldActors[i]);
				auto CannonFireTime = Cannon.GetTimePerFire();
				auto CannonProjectileSpeed = Cannon.GetProjectileSpeed();
				auto CannonProjectileGravity = Cannon.GetProjectileGravityScale();
				auto CannonServerPitch = Cannon.GetServerPitch();

				Actor.cannonProjectileSpeed = CannonProjectileSpeed;
				Actor.cannonProjectileGravityScale = (981.f * CannonProjectileGravity);
				Actor.cannonFireTime = CannonFireTime;
				Actor.cannonServerPitch = CannonServerPitch;

				Actor.objectID = objectID;
				Actor.objectName = objectName;
				Actor.objectPosition = objectPosition;
				Actor.objectDistance = objectDistance;

				tempActorsData.push_back(Actor);
			}
			else
				continue;
		}
		DrawingManager->ActorsData = tempActorsData;
		std::this_thread::sleep_for(std::chrono::milliseconds(16));
	}
}

void cDrawingManager::objectsDataDraw()
{
	auto gameWorld = MemoryManager->Read<cUWorld>(MemoryManager->Read<uintptr_t>(GLOBAL_DEFINITION::UWorld));
	auto LP = gameWorld.GetGameInstance().GetLocalPlayer();
	auto LPController = LP.GetPlayerController();
	auto LPCameraManager = LPController.GetCameraManager();

	SOT->localPlayer.name = W2S->wstringToString(LPController.GetActor().GetPlayerState().GetName());

	SOT->localPlayer.position = LPController.GetActor().GetRootComponent().GetPosition();

	SOT->localCamera.fov = LPCameraManager.GetCameraFOV();
	SOT->localCamera.angles = LPCameraManager.GetCameraRotation();
	SOT->localCamera.position = LPCameraManager.GetCameraPosition();

	auto actorsListCopy = this->ActorsData;

	if (actorsListCopy.size() == 0)
		return;

	for (int i = 0; i < actorsListCopy.size(); ++i)
	{

		ActorsList currentActor = actorsListCopy[i];

		//-> LOCALPLAYER
		if (currentActor.IsLocalPlayer)
		{
			//-> OXYGEN LEVEL
			if (SETTINGS::TOOLS::UTILITY::OXYGEN::oxygenEnabled)
				D3DRenderer->OxygenInfo(currentActor.oxygenLevel);
			continue;
		}

		//-> PLAYERS
		if (SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::showAllies || SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::showEnemies)
		{
			if (currentActor.objectName.find("BP_PlayerPirate_C") != string::npos)
			{
				bool IsRevivable = false;
				bool IsTeammate = false;

				Vector3 oCameraNormalized;
				Vector3 oEnemyNormalized;
				float DistToCrosshair;

				if (currentActor.pirateHealth <= 0)
					IsRevivable = true;

				Vector2 Screen;
				if (W2S->WorldToScreen(currentActor.objectPosition, &Screen))
				{
					Vector3 headPos = Vector3(currentActor.objectPosition.x, currentActor.objectPosition.y, currentActor.objectPosition.z + 90);
					Vector2 ScreenTop;

					if (W2S->WorldToScreen(headPos, &ScreenTop))
					{
						int hi = (Screen.y - ScreenTop.y) * 2.5;
						int wi = hi * 0.5;

						for (int i = 0; i < 24; ++i)
						{
							if (SOT->Pirates[i].name == "")
								continue;

							oCameraNormalized = Vector3(cosf(SOT->localCamera.angles.y), sinf(SOT->localCamera.angles.y), tanf(SOT->localCamera.angles.x)) / Vector3(cosf(SOT->localCamera.angles.y), sinf(SOT->localCamera.angles.y), tanf(SOT->localCamera.angles.x)).Length();
							oEnemyNormalized = (SOT->Pirates[i].position - SOT->localCamera.angles) / (SOT->Pirates[i].position - SOT->localCamera.angles).Length();
							DistToCrosshair = oCameraNormalized.Dot(oEnemyNormalized);

							/*
							-> First Aim Bot Version
							moves the mouse without considering its position in the game, to be rewritten

							if (GetAsyncKeyState(VK_RBUTTON) && DistToCrosshair >= 0.8)
								mouse_event(MOUSEEVENTF_MOVE, ProcessManager->Size[0] + ScreenTop.x, ProcessManager->Size[1] + ScreenTop.y, 0, 0);

							if (GetAsyncKeyState(VK_RBUTTON) && DistToCrosshair >= 0.8 && pirateDistance <= 250)
								//mouse_event(MOUSEEVENTF_MOVE, (ProcessManager->Size[0] / 2 - headPos.x) * -1 * 1, (ProcessManager->Size[1] / 2 - headPos.y) * -1 * 1, 0, 0);
								AimHandler->MouseMove((ProcessManager->Size[0] / 2 - headPos.x) * -1 * 1, (ProcessManager->Size[1] / 2 - headPos.y) * -1 * 1);
							*/

							if (currentActor.pirateName == SOT->Pirates[i].name)
							{
								SOT->Pirates[i].distance = currentActor.objectDistance;
								if (SOT->Pirates[i].crewID == SOT->localPlayer.crewID)
									IsTeammate = true;
							}
						}

						if (SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::showAllies && IsTeammate)
						{
							if (SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::showName)
							{
								if (SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::showHealthPoints)
									D3DRenderer->DrawStringGame(currentActor.pirateName.c_str(), ScreenTop.x, ScreenTop.y - 25, (int)(SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::nameColor[0] * 255.0f), (int)(SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::nameColor[1] * 255.0f), (int)(SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::nameColor[2] * 255.0f), (int)(SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::nameColor[3] * 255.0f), true, true, D3DRenderer->pFontDrawingsSmall);
								else
									D3DRenderer->DrawStringGame(currentActor.pirateName.c_str(), ScreenTop.x, ScreenTop.y - 15, (int)(SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::nameColor[0] * 255.0f), (int)(SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::nameColor[1] * 255.0f), (int)(SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::nameColor[2] * 255.0f), (int)(SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::nameColor[3] * 255.0f), true, true, D3DRenderer->pFontDrawingsSmall);
							}

							if (SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::showHealthBar)
								D3DRenderer->HealthBar(currentActor.pirateHealth, currentActor.pirateMaxHealth, ScreenTop.x - (wi / 25), ScreenTop.y + 1, wi, hi);

							if (SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::showHealthPoints)
								D3DRenderer->DrawStringGame(string("HP: " + to_string((int)currentActor.pirateHealth) + " / " + to_string((int)currentActor.pirateMaxHealth)).c_str(), ScreenTop.x, ScreenTop.y - 15, (int)(SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::nameColor[0] * 255.0f), (int)(SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::nameColor[1] * 255.0f), (int)(SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::nameColor[2] * 255.0f), (int)(SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::nameColor[3] * 255.0f), true, true, D3DRenderer->pFontDrawingsSmall);

							if (SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::showWhenIsDown && IsRevivable)
								D3DRenderer->DrawStringGame("ALLY DOWN", ScreenTop.x, ScreenTop.y - 35, (int)(SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::downColor[0] * 255.0f), (int)(SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::downColor[1] * 255.0f), (int)(SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::downColor[2] * 255.0f), (int)(SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::downColor[3] * 255.0f), true, true, D3DRenderer->pFontDrawingsSmall);

							if (SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::tracelinesType != "DISABLED")
							{
								D3DCOLOR tracelinesColor = D3DCOLOR_XRGB((int)(SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::tracelineColor[0] * 255.0f), (int)(SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::tracelineColor[1] * 255.0f), (int)(SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::tracelineColor[2] * 255.0f));

								if (SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::tracelinesType == "CROSSHAIR")
									D3DRenderer->Line(ScreenTop.x, ScreenTop.y + 90, ProcessManager->Size[0] / 2, ProcessManager->Size[1] / 2, tracelinesColor);
								else if (SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::tracelinesType == "TOP OF SCREEN")
									D3DRenderer->Line(ScreenTop.x, ScreenTop.y + 90, ProcessManager->Size[0] / 2, 15, tracelinesColor);
								else if (SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::tracelinesType == "BOTTOM OF SCREEN")
									D3DRenderer->Line(ScreenTop.x, ScreenTop.y + 90, ProcessManager->Size[0] / 2, ProcessManager->Size[1] - 5, tracelinesColor);
							}

							if (SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::boxType != "DISABLED")
							{
								D3DCOLOR boxColor = D3DCOLOR_XRGB((int)(SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::boxColor[0] * 255.0f), (int)(SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::boxColor[1] * 255.0f), (int)(SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::boxColor[2] * 255.0f));

								if (SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::boxType == "2D FULL BOX")
									D3DRenderer->GameBox(1, ScreenTop.x - wi / 2, ScreenTop.y, wi, hi, boxColor);
								else if (SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::boxType == "2D FULL BOX - BLACK OUTLINE")
									D3DRenderer->GameBox(2, ScreenTop.x - wi / 2, ScreenTop.y, wi, hi, boxColor);
								else if (SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::boxType == "2D FULL BOX - WHITE OUTLINE")
									D3DRenderer->GameBox(3, ScreenTop.x - wi / 2, ScreenTop.y, wi, hi, boxColor);
								else if (SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::boxType == "2D CORNERS BOX")
									D3DRenderer->GameBox(4, ScreenTop.x - wi / 2, ScreenTop.y, wi, hi, boxColor);
								else if (SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::boxType == "2D CORNERS BOX - BLACK OUTLINE")
									D3DRenderer->GameBox(5, ScreenTop.x - wi / 2, ScreenTop.y, wi, hi, boxColor);
								else if (SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::boxType == "2D CORNERS BOX - WHITE OUTLINE")
									D3DRenderer->GameBox(6, ScreenTop.x - wi / 2, ScreenTop.y, wi, hi, boxColor);
							}

							if (SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::showDistance)
							{
								if (SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::showWeapon)
									D3DRenderer->DrawStringGame(string(to_string((int)currentActor.objectDistance) + "m").c_str(), ScreenTop.x, ScreenTop.y + hi + 15, (int)(SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::distanceColor[0] * 255.0f), (int)(SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::distanceColor[1] * 255.0f), (int)(SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::distanceColor[2] * 255.0f), (int)(SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::distanceColor[3] * 255.0f), true, true, D3DRenderer->pFontDrawingsSmall);
								else
									D3DRenderer->DrawStringGame(string(to_string((int)currentActor.objectDistance) + "m").c_str(), ScreenTop.x, ScreenTop.y + hi + 5, (int)(SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::distanceColor[0] * 255.0f), (int)(SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::distanceColor[1] * 255.0f), (int)(SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::distanceColor[2] * 255.0f), (int)(SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::distanceColor[3] * 255.0f), true, true, D3DRenderer->pFontDrawingsSmall);
							}

							if (SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::showWeapon)
							{
								transform(currentActor.pirateItemName.begin(), currentActor.pirateItemName.end(), currentActor.pirateItemName.begin(), ::toupper);
								D3DRenderer->DrawStringGame(currentActor.pirateItemName.c_str(), ScreenTop.x, ScreenTop.y + hi + 5, (int)(SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::weaponColor[0] * 255.0f), (int)(SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::weaponColor[1] * 255.0f), (int)(SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::weaponColor[2] * 255.0f), (int)(SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::weaponColor[3] * 255.0f), true, true, D3DRenderer->pFontDrawingsSmall);
							}
						}
						else if (SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::showEnemies && !IsTeammate)
						{
							if (SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::showName)
							{
								if (SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::showHealthPoints)
									D3DRenderer->DrawStringGame(currentActor.pirateName.c_str(), ScreenTop.x, ScreenTop.y - 25, (int)(SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::nameColor[0] * 255.0f), (int)(SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::nameColor[1] * 255.0f), (int)(SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::nameColor[2] * 255.0f), (int)(SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::nameColor[3] * 255.0f), true, true, D3DRenderer->pFontDrawingsSmall);
								else
									D3DRenderer->DrawStringGame(currentActor.pirateName.c_str(), ScreenTop.x, ScreenTop.y - 15, (int)(SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::nameColor[0] * 255.0f), (int)(SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::nameColor[1] * 255.0f), (int)(SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::nameColor[2] * 255.0f), (int)(SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::nameColor[3] * 255.0f), true, true, D3DRenderer->pFontDrawingsSmall);
							}

							if (SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::showHealthBar)
								D3DRenderer->HealthBar(currentActor.pirateHealth, currentActor.pirateMaxHealth, ScreenTop.x - (wi / 25), ScreenTop.y + 1, wi, hi);

							if (SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::showHealthPoints)
								D3DRenderer->DrawStringGame(string("HP: " + to_string((int)currentActor.pirateHealth) + " / " + to_string((int)currentActor.pirateMaxHealth)).c_str(), ScreenTop.x, ScreenTop.y - 15, (int)(SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::nameColor[0] * 255.0f), (int)(SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::nameColor[1] * 255.0f), (int)(SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::nameColor[2] * 255.0f), (int)(SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::nameColor[3] * 255.0f), true, true, D3DRenderer->pFontDrawingsSmall);

							if (SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::showWhenIsDown && IsRevivable)
								D3DRenderer->DrawStringGame("ENEMY DOWN", ScreenTop.x, ScreenTop.y - 35, (int)(SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::downColor[0] * 255.0f), (int)(SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::downColor[1] * 255.0f), (int)(SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::downColor[2] * 255.0f), (int)(SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::downColor[3] * 255.0f), true, true, D3DRenderer->pFontDrawingsSmall);

							if (SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::tracelinesType != "DISABLED")
							{
								D3DCOLOR tracelinesColor = D3DCOLOR_XRGB((int)(SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::tracelineColor[0] * 255.0f), (int)(SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::tracelineColor[1] * 255.0f), (int)(SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::tracelineColor[2] * 255.0f));

								if (SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::tracelinesType == "CROSSHAIR")
									D3DRenderer->Line(ScreenTop.x, ScreenTop.y + 90, ProcessManager->Size[0] / 2, ProcessManager->Size[1] / 2, tracelinesColor);
								else if (SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::tracelinesType == "TOP OF SCREEN")
									D3DRenderer->Line(ScreenTop.x, ScreenTop.y + 90, ProcessManager->Size[0] / 2, 15, tracelinesColor);
								else if (SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::tracelinesType == "BOTTOM OF SCREEN")
									D3DRenderer->Line(ScreenTop.x, ScreenTop.y + 90, ProcessManager->Size[0] / 2, ProcessManager->Size[1] - 5, tracelinesColor);
							}

							if (SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::boxType != "DISABLED")
							{
								D3DCOLOR boxColor = D3DCOLOR_XRGB((int)(SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::boxColor[0] * 255.0f), (int)(SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::boxColor[1] * 255.0f), (int)(SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::boxColor[2] * 255.0f));

								if (SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::boxType == "2D FULL BOX")
									D3DRenderer->GameBox(1, ScreenTop.x - wi / 2, ScreenTop.y, wi, hi, boxColor);
								else if (SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::boxType == "2D FULL BOX - BLACK OUTLINE")
									D3DRenderer->GameBox(2, ScreenTop.x - wi / 2, ScreenTop.y, wi, hi, boxColor);
								else if (SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::boxType == "2D FULL BOX - WHITE OUTLINE")
									D3DRenderer->GameBox(3, ScreenTop.x - wi / 2, ScreenTop.y, wi, hi, boxColor);
								else if (SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::boxType == "2D CORNERS BOX")
									D3DRenderer->GameBox(4, ScreenTop.x - wi / 2, ScreenTop.y, wi, hi, boxColor);
								else if (SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::boxType == "2D CORNERS BOX - BLACK OUTLINE")
									D3DRenderer->GameBox(5, ScreenTop.x - wi / 2, ScreenTop.y, wi, hi, boxColor);
								else if (SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::boxType == "2D CORNERS BOX - WHITE OUTLINE")
									D3DRenderer->GameBox(6, ScreenTop.x - wi / 2, ScreenTop.y, wi, hi, boxColor);
							}

							if (SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::showDistance)
							{
								if (SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::showWeapon)
									D3DRenderer->DrawStringGame(string(to_string((int)currentActor.objectDistance) + "m").c_str(), ScreenTop.x, ScreenTop.y + hi + 15, (int)(SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::distanceColor[0] * 255.0f), (int)(SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::distanceColor[1] * 255.0f), (int)(SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::distanceColor[2] * 255.0f), (int)(SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::distanceColor[3] * 255.0f), true, true, D3DRenderer->pFontDrawingsSmall);
								else
									D3DRenderer->DrawStringGame(string(to_string((int)currentActor.objectDistance) + "m").c_str(), ScreenTop.x, ScreenTop.y + hi + 5, (int)(SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::distanceColor[0] * 255.0f), (int)(SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::distanceColor[1] * 255.0f), (int)(SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::distanceColor[2] * 255.0f), (int)(SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::distanceColor[3] * 255.0f), true, true, D3DRenderer->pFontDrawingsSmall);
							}

							if (SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::showWeapon)
							{
								transform(currentActor.pirateItemName.begin(), currentActor.pirateItemName.end(), currentActor.pirateItemName.begin(), ::toupper);
								D3DRenderer->DrawStringGame(currentActor.pirateItemName.c_str(), ScreenTop.x, ScreenTop.y + hi + 5, (int)(SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::weaponColor[0] * 255.0f), (int)(SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::weaponColor[1] * 255.0f), (int)(SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::weaponColor[2] * 255.0f), (int)(SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::weaponColor[3] * 255.0f), true, true, D3DRenderer->pFontDrawingsSmall);
							}
						}
					}
				}
			}
		}

		//-> SHIPS
		if (SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ALLY_SHIPS::showShips || SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ENEMY_SHIPS::showShips)
		{
			if (currentActor.objectName.find("BP_SmallShipTemplate_C") != std::string::npos
			|| currentActor.objectName.find("BP_SmallShipNetProxy") != std::string::npos)
			{
				Vector2 Screen;
				if (W2S->WorldToScreen(Vector3(currentActor.objectPosition.x, currentActor.objectPosition.y, currentActor.objectPosition.z + 2000), &Screen))
				{
					if (currentActor.IsShipAllied && SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ALLY_SHIPS::showShips)
						D3DRenderer->DrawGameShip("ALLIED SLOOP", Screen.x, Screen.y, currentActor.objectDistance, (int)(SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ALLY_SHIPS::Color[0] * 255.f), (int)(SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ALLY_SHIPS::Color[1] * 255.f), (int)(SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ALLY_SHIPS::Color[2] * 255.f), (int)(SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ALLY_SHIPS::Color[3] * 255.f), true);
					else if (!currentActor.IsShipAllied && SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ENEMY_SHIPS::showShips)
						D3DRenderer->DrawGameShip("SLOOP", Screen.x, Screen.y, currentActor.objectDistance, (int)(SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ENEMY_SHIPS::Color[0] * 255.f), (int)(SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ENEMY_SHIPS::Color[1] * 255.f), (int)(SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ENEMY_SHIPS::Color[2] * 255.f), (int)(SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ENEMY_SHIPS::Color[3] * 255.f), false);
				}
			}
			else if (currentActor.objectName.find("BP_MediumShipTemplate_C") != std::string::npos
			|| currentActor.objectName.find("BP_MediumShipNetProxy") != std::string::npos)
			{
				Vector2 Screen;
				if (W2S->WorldToScreen(Vector3(currentActor.objectPosition.x, currentActor.objectPosition.y, currentActor.objectPosition.z + 2000), &Screen))
				{
					if (currentActor.IsShipAllied && SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ALLY_SHIPS::showShips)
						D3DRenderer->DrawGameShip("ALLIED BRIGANTINE", Screen.x, Screen.y, currentActor.objectDistance, (int)(SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ALLY_SHIPS::Color[0] * 255.f), (int)(SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ALLY_SHIPS::Color[1] * 255.f), (int)(SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ALLY_SHIPS::Color[2] * 255.f), (int)(SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ALLY_SHIPS::Color[3] * 255.f), true);
					else if (!currentActor.IsShipAllied && SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ENEMY_SHIPS::showShips)
						D3DRenderer->DrawGameShip("BRIGANTINE", Screen.x, Screen.y, currentActor.objectDistance, (int)(SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ENEMY_SHIPS::Color[0] * 255.f), (int)(SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ENEMY_SHIPS::Color[1] * 255.f), (int)(SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ENEMY_SHIPS::Color[2] * 255.f), (int)(SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ENEMY_SHIPS::Color[3] * 255.f), false);
				}
			}
			else if (currentActor.objectName.find("BP_LargeShipTemplate_C") != std::string::npos
			|| currentActor.objectName.find("BP_LargeShipNetProxy") != std::string::npos)
			{
				Vector2 Screen;
				if (W2S->WorldToScreen(Vector3(currentActor.objectPosition.x, currentActor.objectPosition.y, currentActor.objectPosition.z + 2000), &Screen))
				{
					D3DRenderer->DrawGameShip(currentActor.shipTeam.c_str(), Screen.x, Screen.y - 50, currentActor.objectDistance, (int)(SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ALLY_SHIPS::Color[0] * 255.f), (int)(SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ALLY_SHIPS::Color[1] * 255.f), (int)(SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ALLY_SHIPS::Color[2] * 255.f), (int)(SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ALLY_SHIPS::Color[3] * 255.f), true);

					if (currentActor.IsShipAllied && SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ALLY_SHIPS::showShips)
						D3DRenderer->DrawGameShip("ALLIED GALLEON", Screen.x, Screen.y, currentActor.objectDistance, (int)(SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ALLY_SHIPS::Color[0] * 255.f), (int)(SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ALLY_SHIPS::Color[1] * 255.f), (int)(SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ALLY_SHIPS::Color[2] * 255.f), (int)(SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ALLY_SHIPS::Color[3] * 255.f), true);
					else if (!currentActor.IsShipAllied && SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ENEMY_SHIPS::showShips && !SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ENEMY_SHIPS::UniqueColorsForCrews)
						D3DRenderer->DrawGameShip("GALLEON", Screen.x, Screen.y, currentActor.objectDistance, (int)(SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ENEMY_SHIPS::Color[0] * 255.f), (int)(SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ENEMY_SHIPS::Color[1] * 255.f), (int)(SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ENEMY_SHIPS::Color[2] * 255.f), (int)(SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ENEMY_SHIPS::Color[3] * 255.f), false);
					else if (!currentActor.IsShipAllied && SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ENEMY_SHIPS::showShips && SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ENEMY_SHIPS::UniqueColorsForCrews)
						D3DRenderer->DrawGameShip("GALLEON", Screen.x, Screen.y, currentActor.objectDistance, get<0>(D3DRenderer->getShipColor(currentActor.shipTeam)), get<1>(D3DRenderer->getShipColor(currentActor.shipTeam)), get<2>(D3DRenderer->getShipColor(currentActor.shipTeam)), get<3>(D3DRenderer->getShipColor(currentActor.shipTeam)), false);
				}
			}

			/*
			-> Rowboats need to be fixed, its showing boats even if there's no rowboat
			
			else if (SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ROWBOATS::showRowboats
			&& (currentActor.objectName.find("BP_Rowboat_C") != std::string::npos
			|| currentActor.objectName.find("BP_RowboatRowingSeat_C") != std::string::npos
			|| currentActor.objectName.find("BP_Rowboat_WithFrontHarpoon_C") != std::string::npos))
			{
				Vector2 Screen;
				if (W2S->WorldToScreen(Vector3(currentActor.objectPosition.x, currentActor.objectPosition.y, currentActor.objectPosition.z + 2000), &Screen))
					D3DRenderer->DrawGameShip("ROWBOAT", Screen.x, Screen.y, currentActor.objectDistance, ((int)SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ROWBOATS::rowboatColor[0] * 255.f), ((int)SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ROWBOATS::rowboatColor[1] * 255.f), ((int)SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ROWBOATS::rowboatColor[2] * 255.f), ((int)SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ROWBOATS::rowboatColor[3] * 255.f));
			}
			*/
		}

		//-> ITEMS/CHESTS INFO
		if (SETTINGS::TOOLS::TREASURES_ESP::GENERAL::treasuresESPEnabled)
		{
			if (currentActor.objectName.find("Proxy") != string::npos && currentActor.objectName.find("NetProxy") == string::npos)
			{
				Vector2 Screen;
				if (W2S->WorldToScreen(currentActor.objectPosition, &Screen))
					D3DRenderer->DrawGameObject(W2S->wstringToString(currentActor.treasureName).c_str(), Screen.x, Screen.y, currentActor.objectDistance, get<0>(D3DRenderer->getTreasureColor(currentActor.objectName)), get<1>(D3DRenderer->getTreasureColor(currentActor.objectName)), get<2>(D3DRenderer->getTreasureColor(currentActor.objectName)), get<3>(D3DRenderer->getTreasureColor(currentActor.objectName)));
			}
			else if (DataManager->IsA(CHEST, currentActor.objectName))
			{
				Vector2 Screen;
				if (W2S->WorldToScreen(currentActor.objectPosition, &Screen))
					D3DRenderer->DrawGameObject("AMMO CHEST", Screen.x, Screen.y, currentActor.objectDistance, get<0>(D3DRenderer->getTreasureColor(currentActor.objectName)), get<1>(D3DRenderer->getTreasureColor(currentActor.objectName)), get<2>(D3DRenderer->getTreasureColor(currentActor.objectName)), get<3>(D3DRenderer->getTreasureColor(currentActor.objectName)));
			}
		}

		if (currentActor.objectName.find("DamageZone") != string::npos)
		{
			Vector2 Screen;
			if (W2S->WorldToScreen(currentActor.objectPosition, &Screen))
				D3DRenderer->DrawGameObject("x", Screen.x, Screen.y, currentActor.objectDistance, get<0>(D3DRenderer->getTreasureColor(currentActor.objectName)), get<1>(D3DRenderer->getTreasureColor(currentActor.objectName)), get<2>(D3DRenderer->getTreasureColor(currentActor.objectName)), get<3>(D3DRenderer->getTreasureColor(currentActor.objectName)));
		}

		if (currentActor.objectName.find("BP_Cannon_C") != string::npos)
		{
			char testbuf[64];
			snprintf(testbuf, sizeof(testbuf), "PS: %.2f / GS: %.2f / FT: %.2f / SP: %.2f", currentActor.cannonProjectileSpeed, currentActor.cannonProjectileGravityScale, currentActor.cannonFireTime, currentActor.cannonServerPitch);
				
			Vector2 Screen;
			if (W2S->WorldToScreen(currentActor.objectPosition, &Screen))
			{
				D3DRenderer->DrawStringGame(testbuf, Screen.x, Screen.y + 25, 255, 255, 255, 255, true, false, D3DRenderer->pFontDrawingsSmall);
			}
		}

		/*
		-> Levels reading without performance loss?
		
		if (currentActor.objectName.find("BP_IslandStorageBarrel") != string::npos)
		{
			Vector2 Screen;
			if (W2S->WorldToScreen(currentActor.objectPosition, &Screen))
				D3DRenderer->DrawGameObject("ISLAND BARREL", Screen.x, Screen.y, currentActor.objectDistance, get<0>(D3DRenderer->getTreasureColor(currentActor.objectName)), get<1>(D3DRenderer->getTreasureColor(currentActor.objectName)), get<2>(D3DRenderer->getTreasureColor(currentActor.objectName)), get<3>(D3DRenderer->getTreasureColor(currentActor.objectName)));
		}
		*/
	}
}


//-> DEBUG MODE
void objectsDebugDataShare()
{
	while (true)
	{
		if (SETTINGS::MENU::DebugMode)
		{
			vector<ActorsList> tempActorsDebugData;

			auto gameWorld = MemoryManager->Read<cUWorld>(MemoryManager->Read<uintptr_t>(GLOBAL_DEFINITION::UWorld));
			auto allWorlds = MemoryManager->Read<AllWorlds>(MemoryManager->Read<uintptr_t>(GLOBAL_DEFINITION::UWorld));
			auto LP = gameWorld.GetGameInstance().GetLocalPlayer();
			auto LPController = LP.GetPlayerController();
			auto LPCameraManager = LPController.GetCameraManager();

			SOT->localPlayer.name = W2S->wstringToString(LPController.GetActor().GetPlayerState().GetName());

			SOT->localPlayer.position = LPController.GetActor().GetRootComponent().GetPosition();

			SOT->localCamera.fov = LPCameraManager.GetCameraFOV();
			SOT->localCamera.angles = LPCameraManager.GetCameraRotation();
			SOT->localCamera.position = LPCameraManager.GetCameraPosition();

			auto worldLevel = gameWorld.GetLevel();
			auto worldActors = worldLevel.GetActors();

			if (!worldActors.IsValid())
				return;

			TArray <class ULevel*> allLevels = allWorlds.GetAllLevels();

			if (allLevels.Length() == 0)
				return;

			for (int levelIndex = 0; levelIndex < allLevels.Length(); levelIndex++)
			{
				auto levelActors = allLevels[levelIndex].GetActors();

				if (levelActors.Length() == 0)
					return;

				for (int i = 0; i < levelActors.Length(); ++i)
				{
					auto objectActor = *reinterpret_cast<AActor*>(&levelActors[i]);

					if (objectActor == LPController.GetActor())
					{
						auto objectCharacter = *reinterpret_cast<ACharacter*>(&worldActors[i]);

						ActorsList Actor{};
						Actor.IsLocalPlayer = true;
						Actor.oxygenLevel = objectCharacter.GetDrowningComponent().GetOxygenLevel();
						tempActorsDebugData.push_back(Actor);

						continue;
					}

					auto objectID = objectActor.GetID();
					auto objectName = DrawingManager->getNameFromIDmem(objectID);
					auto objectPosition = objectActor.GetRootComponent().GetPosition();
					auto objectDistance = SOT->localCamera.position.DistTo(objectPosition) / 100.00f;

					
					ActorsList Actor{};

					Actor.objectID = objectID;
					Actor.objectName = objectName;
					Actor.objectPosition = objectPosition;
					Actor.objectDistance = objectDistance;

					tempActorsDebugData.push_back(Actor);
				}
			}
			DrawingManager->ActorsDebugData = tempActorsDebugData;
			std::this_thread::sleep_for(std::chrono::milliseconds(2500));
		}
	}
}

void cDrawingManager::objectsDebugDataDraw()
{
	auto gameWorld = MemoryManager->Read<cUWorld>(MemoryManager->Read<uintptr_t>(GLOBAL_DEFINITION::UWorld));
	auto LP = gameWorld.GetGameInstance().GetLocalPlayer();
	auto LPController = LP.GetPlayerController();
	auto LPCameraManager = LPController.GetCameraManager();

	SOT->localPlayer.name = W2S->wstringToString(LPController.GetActor().GetPlayerState().GetName());

	SOT->localPlayer.position = LPController.GetActor().GetRootComponent().GetPosition();

	SOT->localCamera.fov = LPCameraManager.GetCameraFOV();
	SOT->localCamera.angles = LPCameraManager.GetCameraRotation();
	SOT->localCamera.position = LPCameraManager.GetCameraPosition();

	auto actorsDebugListCopy = this->ActorsDebugData;
	if (actorsDebugListCopy.size() == 0)
		return;

	for (int i = 0; i < actorsDebugListCopy.size(); ++i)
	{
		ActorsList currentActor = actorsDebugListCopy[i];

		if (currentActor.IsLocalPlayer)
			continue;

		if (currentActor.objectDistance > SETTINGS::MENU::DebugModeMaxRenderDistance)
			continue;

		Vector2 Screen;
		if (W2S->WorldToScreen(currentActor.objectPosition, &Screen))
			D3DRenderer->DrawGameObjectDebug(currentActor.objectName.c_str(), Screen.x, Screen.y + (0.2 * i), currentActor.objectDistance, get<0>(D3DRenderer->getTreasureColor(currentActor.objectName)), get<1>(D3DRenderer->getTreasureColor(currentActor.objectName)), get<2>(D3DRenderer->getTreasureColor(currentActor.objectName)), get<3>(D3DRenderer->getTreasureColor(currentActor.objectName)));
	}
}
