#include "../Overlay/UIRenderer.h"

bool bFirstTime = true;

cUIRenderer* UIRenderer = new cUIRenderer();

cUIRenderer::cUIRenderer()
{
}

cUIRenderer::~cUIRenderer()
{
}

void cUIRenderer::DrawInfo(IDirect3DDevice9* pDevice)
{
	char SET_NameBuf[48]; 
	sprintf(SET_NameBuf, "KingCU.cc | Sea of Thieves | Beta");
	printf(" Made By Buck3ts41 ");
	D3DRenderer->DrawStringOutline(SET_NameBuf, 15, (float)(ProcessManager->Size[1] * 0.020f), 110, 164, 235, 255, D3DRenderer->pFontUIMedium);
	
	char SET_InfoBuf[256];
	sprintf(SET_InfoBuf, "FPS: %u\n\n\INSERT » Open Menu\nEND » Panic Key\nF5 » Save Settings\nF6 » Load Settings", GLOBAL_DEFINITION::FramesPerSecond);
	D3DRenderer->DrawStringOutline(SET_InfoBuf, 15, 35, 255, 255, 255, 200, D3DRenderer->pFontUISmall);
	
	char SET_DebugBuf[256];
	sprintf(SET_DebugBuf, "Base Module: %lld\nBase Module Size: %lld\nUWorld: %lld\nGNames: %lld\nGObjects: %lld",
		GLOBAL_DEFINITION::baseModule, GLOBAL_DEFINITION::baseModuleSize, GLOBAL_DEFINITION::UWorld, GLOBAL_DEFINITION::GNames, GLOBAL_DEFINITION::GObjects);
	D3DRenderer->DrawStringOutline(SET_DebugBuf, 15, GLOBAL_DEFINITION::rHeight - 75, 255, 255, 255, 255, D3DRenderer->pFontUISmall);
}

void cUIRenderer::DrawMenu(IDirect3DDevice9* pDevice)
{
	UIHandler->loadUIStyles();
	ImGui_ImplDX9_NewFrame();

	ImGui::Begin("[ KingCU.cc External Menu ]", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
	ImGui::SetWindowSize({ 850, 515 }, ImGuiCond_Always);

	for (int i = 0; i < _countof(SETTINGS::MENU::menuTabs); ++i)
	{
		bool buttonState = false;
		(SETTINGS::MENU::activeMenuTab) == i ? buttonState = true : buttonState = false;
		ImGui::SameLine();
		UIHandler->drawButton(SETTINGS::MENU::menuTabs[i], i, "GENERAL_TAB", buttonState, 110, 30);
	}

	if (SETTINGS::MENU::activeMenuTab == 0) //-> GENERAL TAB
	{
		ImGui::BeginChild("SOT_EXTERNAL_TOOL_GENERAL_TAB", ImVec2(835, 445), true);

		
		ImGui::Text("This cheat is in BETA testing, feel free to");
		ImGui::Text("contact developer for any bugs/issue you find : )");
		ImGui::NewLine();
		ImGui::Text("            Buck3ts41       ");

		ImGui::EndChild();
	}
	else if (SETTINGS::MENU::activeMenuTab == 1) //-> TREASURES TAB
	{
		ImGui::BeginChild("SOT_EXTERNAL_TOOL_TREASURES_ESP_MENU", ImVec2(835, 40), true);
		for (int i = 0; i < _countof(SETTINGS::MENU::menuTabs_treasures); ++i)
		{
			bool buttonState = false;
			(SETTINGS::MENU::activeMenuTab_treasures) == i ? buttonState = true : buttonState = false;
			ImGui::SameLine();
			ImGui::SetCursorPosX(835 - 828 + (75 * i) + (8 * i));
			UIHandler->drawButton(SETTINGS::MENU::menuTabs_treasures[i], i, "SIDE_TAB_TREASURES", buttonState, 75, 22);
		}
		ImGui::EndChild();

		if (SETTINGS::MENU::activeMenuTab_treasures == 0)
		{
			ImGui::BeginChild("SOT_EXTERNAL_TOOL_TREASURES_TAB_0_1", ImVec2(413, 400), true);
			UIHandler->UIChildHeaderSingle("GENERAL SETTINGS", true, 413);

			ImGui::Checkbox("ENABLE TREASURES ESP", &SETTINGS::TOOLS::TREASURES_ESP::GENERAL::treasuresESPEnabled);

			ImGui::Dummy(ImVec2(0.0f, 10.f));
			UIHandler->UIChildHeaderSingle("DISTANCE FONT DRAWING SETTINGS", true, 413);
			
			if (!SETTINGS::TOOLS::TREASURES_ESP::GENERAL::treasuresGeneralDistance) ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
			ImGui::SliderInt("MAX LOW DISTANCE", &SETTINGS::TOOLS::TREASURES_ESP::GENERAL::treasuresGeneralDistanceLow, 0, SETTINGS::TOOLS::TREASURES_ESP::GENERAL::treasuresGeneralDistanceMedium - 1, "%.0f");
			UIHandler->HelpMarker("Depending on the distance between You and the object, its name will be displayed in a larger or smaller font\n(the settings of a given treasure regarding this functionality will be ignored)...", false, false);
			ImGui::SliderInt("MAX MEDIUM DISTANCE", &SETTINGS::TOOLS::TREASURES_ESP::GENERAL::treasuresGeneralDistanceMedium, SETTINGS::TOOLS::TREASURES_ESP::GENERAL::treasuresGeneralDistanceLow, 1000, "%.0f");
			if (!SETTINGS::TOOLS::TREASURES_ESP::GENERAL::treasuresGeneralDistance) ImGui::PopItemFlag();

			ImGui::EndChild();
			ImGui::SameLine();

			ImGui::BeginChild("SOT_EXTERNAL_TOOL_TREASURES_TAB_0_2", ImVec2(413, 400), true);
			UIHandler->UIChildHeaderSingle("TREASURES COLORS SETTINGS", true, 413);

			ImGui::Checkbox("ENABLE GENERAL TREASURES ESP COLORS", &SETTINGS::TOOLS::TREASURES_ESP::GENERAL::treasuresGeneralColors);
			UIHandler->HelpMarker("Use the default color set for all treasures of a given type\n(by disabling this option, the colors will be displayed individually for each treasure,\nyou can edit them in the appropriate treasure tab)...", false, false);
			if (!SETTINGS::TOOLS::TREASURES_ESP::GENERAL::treasuresESPEnabled) ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
			ImGui::ColorEdit4("COMMON COLOR", (float*)&SETTINGS::TOOLS::TREASURES_ESP::GENERAL::treasuresCommonColor);
			ImGui::ColorEdit4("RARE COLOR", (float*)&SETTINGS::TOOLS::TREASURES_ESP::GENERAL::treasuresRareColor);
			ImGui::ColorEdit4("EPIC COLOR", (float*)&SETTINGS::TOOLS::TREASURES_ESP::GENERAL::treasuresEpicColor);
			ImGui::ColorEdit4("MYTHICAL COLOR", (float*)&SETTINGS::TOOLS::TREASURES_ESP::GENERAL::treasuresMythicalColor);
			ImGui::ColorEdit4("LEGENDARY COLOR", (float*)&SETTINGS::TOOLS::TREASURES_ESP::GENERAL::treasuresLegendaryColor);
			ImGui::ColorEdit4("MERCHANT COLOR", (float*)&SETTINGS::TOOLS::TREASURES_ESP::GENERAL::treasuresMerchantColor);
			ImGui::ColorEdit4("LORE BOOKS COLOR", (float*)&SETTINGS::TOOLS::TREASURES_ESP::GENERAL::treasuresLoreBooksColor);
			ImGui::ColorEdit4("QUEST COLOR", (float*)&SETTINGS::TOOLS::TREASURES_ESP::GENERAL::treasuresQuestsColor);
			ImGui::ColorEdit4("OTHER COLOR", (float*)&SETTINGS::TOOLS::TREASURES_ESP::GENERAL::treasuresOthersColor);
			if (!SETTINGS::TOOLS::TREASURES_ESP::GENERAL::treasuresESPEnabled) ImGui::PopItemFlag();

			ImGui::EndChild();
		}
		
	}
	else if (SETTINGS::MENU::activeMenuTab == 2) //-> OBJECTS TAB
	{
		ImGui::BeginChild("SOT_EXTERNAL_TOOL_OBJECTS_ESP_MENU", ImVec2(835, 40), true);
		for (int i = 0; i < _countof(SETTINGS::MENU::menuTabs_objects); ++i)
		{
			bool buttonState = false;
			(SETTINGS::MENU::activeMenuTab_objects) == i ? buttonState = true : buttonState = false;
			ImGui::SameLine();
			ImGui::SetCursorPosX(835 - 738 + (85 * i) + (8 * i));
			UIHandler->drawButton(SETTINGS::MENU::menuTabs_objects[i], i, "SIDE_TAB_OBJECTS", buttonState, 85, 22);
		}
		ImGui::EndChild();

		if (SETTINGS::MENU::activeMenuTab_objects == 1) //-> PLAYERS
		{
			ImGui::BeginChild("SOT_EXTERNAL_TOOL_OBJECTS_TAB_ALLIES", ImVec2(413, 400), true);
			UIHandler->UIChildHeaderSingle("ALLY PLAYERS", true, 413);
			ImGui::Checkbox("SHOW ALLIES", &SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::showAllies);
			ImGui::Checkbox("SHOW NAME", &SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::showName);
			ImGui::ColorEdit4("NAME COLOR", (float*)&SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::nameColor);
			ImGui::Checkbox("SHOW HEALTH BAR", &SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::showHealthBar);
			ImGui::SameLine();
			ImGui::Checkbox("SHOW HEALTH POINTS", &SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::showHealthPoints);
			ImGui::Checkbox("SHOW WHEN IS DOWN", &SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::showWhenIsDown);
			ImGui::ColorEdit4("DOWN COLOR", (float*)&SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::downColor);
			if (ImGui::BeginCombo("ALLY TRACELINES", SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::tracelinesType))
			{
				for (int n = 0; n < _countof(SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::tracelinesTypes); n++)
				{
					bool is_selected = (SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::tracelinesType == SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::tracelinesTypes[n]);
					if (ImGui::Selectable(SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::tracelinesTypes[n], is_selected))
						SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::tracelinesType = SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::tracelinesTypes[n];
					if (is_selected)
						ImGui::SetItemDefaultFocus();
				}
				ImGui::EndCombo();
			}
			ImGui::ColorEdit3("TRACELINES COLOR", (float*)&SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::tracelineColor);
			if (ImGui::BeginCombo("BOX TYPE", SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::boxType))
			{
				for (int n = 0; n < _countof(SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::boxTypes); n++)
				{
					bool is_selected = (SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::boxType == SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::boxTypes[n]);
					if (ImGui::Selectable(SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::boxTypes[n], is_selected))
						SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::boxType = SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::boxTypes[n];
					if (is_selected)
						ImGui::SetItemDefaultFocus();
				}
				ImGui::EndCombo();
			}
			ImGui::ColorEdit3("BOX COLOR", (float*)&SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::boxColor);
			ImGui::Checkbox("SHOW DISTANCE", &SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::showDistance);
			ImGui::ColorEdit4("DISTANCE COLOR", (float*)&SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::distanceColor);
			ImGui::Checkbox("SHOW WEAPON NAME" , &SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::showWeapon);
			ImGui::ColorEdit4("WEAPON NAME COLOR", (float*)&SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ALLIES::weaponColor);
			ImGui::EndChild();

			ImGui::SameLine();

			ImGui::BeginChild("SOT_EXTERNAL_TOOL_OBJECTS_TAB_ENEMIES", ImVec2(413, 400), true);
			UIHandler->UIChildHeaderSingle("ENEMY PLAYERS", true, 413);
			ImGui::Checkbox("SHOW ENEMIES", &SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::showEnemies);
			ImGui::Checkbox("SHOW NAME", &SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::showName);
			ImGui::ColorEdit4("NAME COLOR", (float*)&SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::nameColor);
			ImGui::Checkbox("SHOW HEALTH BAR", &SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::showHealthBar);
			ImGui::SameLine();
			ImGui::Checkbox("SHOW HEALTH POINTS", &SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::showHealthPoints);
			ImGui::Checkbox("SHOW WHEN IS DOWN", &SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::showWhenIsDown);
			ImGui::ColorEdit4("DOWN COLOR", (float*)&SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::downColor);
			if (ImGui::BeginCombo("ENEMY TRACELINES", SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::tracelinesType))
			{
				for (int n = 0; n < _countof(SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::tracelinesTypes); n++)
				{
					bool is_selected = (SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::tracelinesType == SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::tracelinesTypes[n]);
					if (ImGui::Selectable(SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::tracelinesTypes[n], is_selected))
						SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::tracelinesType = SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::tracelinesTypes[n];
					if (is_selected)
						ImGui::SetItemDefaultFocus();
				}
				ImGui::EndCombo();
			}
			ImGui::ColorEdit3("TRACELINES COLOR", (float*)&SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::tracelineColor);
			if (ImGui::BeginCombo("BOX TYPE", SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::boxType))
			{
				for (int n = 0; n < _countof(SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::boxTypes); n++)
				{
					bool is_selected = (SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::boxType == SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::boxTypes[n]);
					if (ImGui::Selectable(SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::boxTypes[n], is_selected))
						SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::boxType = SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::boxTypes[n];
					if (is_selected)
						ImGui::SetItemDefaultFocus();
				}
				ImGui::EndCombo();
			}
			ImGui::ColorEdit3("BOX COLOR", (float*)&SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::boxColor);
			ImGui::Checkbox("SHOW DISTANCE", &SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::showDistance);
			ImGui::ColorEdit4("DISTANCE COLOR", (float*)&SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::distanceColor);
			ImGui::Checkbox("SHOW WEAPON NAME", &SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::showWeapon);
			ImGui::ColorEdit4("WEAPON NAME COLOR", (float*)&SETTINGS::TOOLS::OBJECTS_ESP::PLAYERS::ENEMIES::weaponColor);
			ImGui::EndChild();
		}
		else if (SETTINGS::MENU::activeMenuTab_objects == 2) //-> SHIPS
		{
			ImGui::BeginChild("SOT_EXTERNAL_TOOL_OBJECTS_TAB_ALLIED_SHIPS", ImVec2(413, 400), true);
			UIHandler->UIChildHeaderSingle("ALLIED SHIPS SETTINGS", true, 413);

			ImGui::Checkbox("SHOW ALLIED SHIPS", &SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ALLY_SHIPS::showShips);
			ImGui::ColorEdit4("NAME COLOR", (float*)&SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ALLY_SHIPS::Color);
			ImGui::Checkbox("SHOW DISTANCE", &SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ALLY_SHIPS::Distance);
			ImGui::SliderInt("MAX RENDER DISTANCE", &SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ALLY_SHIPS::MaxDistanceToRender, 0, 20000, "%.0f");
			ImGui::Checkbox("SHOW VELOCITY", &SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ALLY_SHIPS::Velocity);
			ImGui::Checkbox("SHOW HEALTH", &SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ALLY_SHIPS::Health);
			ImGui::Checkbox("SHOW WATER LEVEL", &SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ALLY_SHIPS::Water);
			//

			ImGui::Checkbox("SHOW DAMAGE ZONES", &SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ALLY_SHIPS::DamageZones);
			ImGui::ColorEdit4("DAMAGE ZONES COLOR", (float*)&SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ALLY_SHIPS::DamageZonesColor);
			ImGui::SliderInt("MAX DISTANCE", &SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ALLY_SHIPS::DamageZonesMaxDistance, 0, 20000, "%.0f");
			ImGui::Checkbox("SHOW AMMO WHEN USE CANNON", &SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ALLY_SHIPS::ShowAmmo);

			ImGui::EndChild();
			ImGui::SameLine();

			ImGui::BeginChild("SOT_EXTERNAL_TOOL_OBJECTS_TAB_ENEMY_SHIPS", ImVec2(413, 400), true);
			UIHandler->UIChildHeaderSingle("ENEMY SHIPS SETTINGS", true, 413);

			ImGui::Checkbox("SHOW ENEMY SHIPS", &SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ENEMY_SHIPS::showShips);
			ImGui::Checkbox("UNIQUE NAME COLORS FOR CREWS", &SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ENEMY_SHIPS::UniqueColorsForCrews);
			UIHandler->HelpMarker("Enabling this feature will display names of ships in the appropriate type of colors.", false, false);
			if (SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ENEMY_SHIPS::UniqueColorsForCrews)
			{
				ImGui::ColorEdit4("FIRST TEAM COLOR", (float*)&SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ENEMY_SHIPS::AzureScoutColor);
				ImGui::ColorEdit4("SECOND TEAM COLOR", (float*)&SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ENEMY_SHIPS::RegalHoundColor);
				ImGui::ColorEdit4("THIRD TEAM COLOR", (float*)&SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ENEMY_SHIPS::LuckyRoverColor);
				ImGui::ColorEdit4("FOURTH TEAM COLOR", (float*)&SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ENEMY_SHIPS::FlamingJackalColor);
				ImGui::ColorEdit4("FIFTHT EAM COLOR", (float*)&SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ENEMY_SHIPS::GoldenChaserColor);
			}
			else
				ImGui::ColorEdit4("NAME COLOR", (float*)&SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ENEMY_SHIPS::Color);
			ImGui::Checkbox("EMISSARY FLAG IN NAME", &SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ENEMY_SHIPS::ShowEmissaryFlagInName);
			UIHandler->HelpMarker("Enabling this setting will display the name of the emissary companies\nfor which the ship is sailing, it will be one of the following companies:\n- Gold Hoarders\n- Order of Souls\n-Athena's Fortune\n-Reaper's Bones\n-Merchant Alliance.", false, false);

			ImGui::Checkbox("SHOW DISTANCE", &SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ENEMY_SHIPS::Distance);
			ImGui::SliderInt("MAX RENDER DISTANCE", &SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ENEMY_SHIPS::MaxDistanceToRender, 0, 20000, "%.0f");
			ImGui::Checkbox("SHOW VELOCITY", &SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ENEMY_SHIPS::Velocity);
			ImGui::Checkbox("SHOW HEALTH", &SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ENEMY_SHIPS::Health);
			ImGui::Checkbox("SHOW WATER LEVEL", &SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ENEMY_SHIPS::Water);
			//

			ImGui::Checkbox("SHOW DAMAGE ZONES", &SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ENEMY_SHIPS::DamageZones);
			ImGui::ColorEdit4("DAMAGE ZONES COLOR", (float*)&SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ENEMY_SHIPS::DamageZonesColor);
			ImGui::SliderInt("MAX DISTANCE", &SETTINGS::TOOLS::OBJECTS_ESP::SHIPS::ENEMY_SHIPS::DamageZonesMaxDistance, 0, 20000, "%.0f");

			ImGui::EndChild();
		}
		else
		{
			ImGui::BeginChild("SOT_EXTERNAL_TOOL_OBJECTS_TAB", ImVec2(835, 400), true);
			UIHandler->UIChildHeaderSingle(SETTINGS::MENU::menuTabs_objects[SETTINGS::MENU::activeMenuTab_objects], false, 835);
			ImGui::EndChild();
		}
	}
	//else if (SETTINGS::MENU::activeMenuTab == 3) //-> AIMBOT TAB
	//{
		//ImGui::BeginChild("SOT_EXTERNAL_TOOL_AIMHELPER_TAB", ImVec2(835, 445), true);

		//UIHandler->UIChildHeaderSingle("AIM HELPER", false, 835);

		//if (ImGui::Button("save"))
		//{}

		//if (ImGui::Button("load"))
		//{}

		//ImGui::EndChild();
	//}
	//else if (SETTINGS::MENU::activeMenuTab == 4) //-> MISC TAB
	//{
		//ImGui::BeginChild("SOT_EXTERNAL_TOOL_MISC_TAB", ImVec2(835, 445), true);

		//ImGui::ShowStyleEditor();

		//ImGui::EndChild();
	//}
	else if (SETTINGS::MENU::activeMenuTab == 5) //-> UTILITY TAB
	{
		ImGui::BeginChild("SOT_EXTERNAL_TOOL_UTILITY_TAB_FIRST", ImVec2(413, 445), true);
		UIHandler->UIChildHeaderSingle("CROSSHAIR SETTINGS", true, 413);

		ImGui::Checkbox("SHOW CROSSHAIR", &SETTINGS::TOOLS::UTILITY::CROSSHAIR::crosshairEnabled);
		ImGui::Checkbox("CROSSHAIR GRADIENT", &SETTINGS::TOOLS::UTILITY::CROSSHAIR::crosshairGradient);
		if (SETTINGS::TOOLS::UTILITY::CROSSHAIR::crosshairGradient)
		{
			if (ImGui::BeginCombo("GRADIENT TYPE", SETTINGS::TOOLS::UTILITY::CROSSHAIR::crosshairGradientType))
			{
				for (int n = 0; n < 2; n++)
				{
					bool is_selected = (SETTINGS::TOOLS::UTILITY::CROSSHAIR::crosshairGradientType == SETTINGS::TOOLS::UTILITY::CROSSHAIR::crosshairGradientTypes[n]);
					if (ImGui::Selectable(SETTINGS::TOOLS::UTILITY::CROSSHAIR::crosshairGradientTypes[n], is_selected))
						SETTINGS::TOOLS::UTILITY::CROSSHAIR::crosshairGradientType = SETTINGS::TOOLS::UTILITY::CROSSHAIR::crosshairGradientTypes[n];
					if (is_selected)
						ImGui::SetItemDefaultFocus();
				}
				ImGui::EndCombo();
			}
			ImGui::ColorEdit3("FIRST COLOR", (float*)&SETTINGS::TOOLS::UTILITY::CROSSHAIR::crosshairStartColor);
			ImGui::ColorEdit3("SECOND COLOR", (float*)&SETTINGS::TOOLS::UTILITY::CROSSHAIR::crosshairEndColor);
		}
		else {
			ImGui::ColorEdit3("CROSSHAIR COLOR", (float*)&SETTINGS::TOOLS::UTILITY::CROSSHAIR::crosshairColor);
		}
		ImGui::SliderFloat("CROSSHAIR SIZE", &SETTINGS::TOOLS::UTILITY::CROSSHAIR::crosshairSize, 3.f, 25.f, "%.1fpx");
		ImGui::SliderFloat("CROSSHAIR THICKNESS", &SETTINGS::TOOLS::UTILITY::CROSSHAIR::crosshairThickness, 1.f, 10.f, "%.1fpx");

		ImGui::Dummy(ImVec2(0.0f, 10.f));
		UIHandler->UIChildHeaderSingle("COMPASS SETTINGS", true, 413);

		ImGui::Checkbox("SHOW COMPASS", &SETTINGS::TOOLS::UTILITY::COMPASS::compassEnabled);
		ImGui::Checkbox("SHOW FULL NAME OF DIRECTION", &SETTINGS::TOOLS::UTILITY::COMPASS::compassFullName);
		UIHandler->HelpMarker("Show full name of direction youre looking at\neg. North East, instead of NE...", false, false);
		ImGui::Checkbox("SHOW PLAYER'S VELOCITY", &SETTINGS::TOOLS::UTILITY::COMPASS::compassSpeed);
		ImGui::SliderInt("COMPASS SIZE", &SETTINGS::TOOLS::UTILITY::COMPASS::compassSize, 1, 3, "%.0f");
		ImGui::ColorEdit4("COMPASS COLOR", (float*)&SETTINGS::TOOLS::UTILITY::COMPASS::compassColor);

		ImGui::Dummy(ImVec2(0.0f, 10.f));
		UIHandler->UIChildHeaderSingle("OXYGEN SETTINGS", true, 413);

		ImGui::Checkbox("SHOW OXYGEN LEVEL", &SETTINGS::TOOLS::UTILITY::OXYGEN::oxygenEnabled);
		ImGui::ColorEdit4("OXYGEN COLOR", (float*)&SETTINGS::TOOLS::UTILITY::OXYGEN::oxygenColor);
		ImGui::Checkbox("SHOW LOW OXYGEN LEVEL WARNING", &SETTINGS::TOOLS::UTILITY::OXYGEN::oxygenWarning);
		UIHandler->HelpMarker("Show the low oxygen (less than 15%) warning in the center of the screen...", false, false);
		ImGui::ColorEdit4("WARNING COLOR", (float*)&SETTINGS::TOOLS::UTILITY::OXYGEN::oxygenWarningColor);
		
		
		ImGui::EndChild();

		ImGui::SameLine();

		ImGui::BeginChild("SOT_EXTERNAL_TOOL__UTILITY_TAB_SECOND", ImVec2(413, 445), true);
		
		UIHandler->UIChildHeaderSingle("GENERAL SETTINGS", true, 413);

		ImGui::Checkbox("LOW END PC MODE", &SETTINGS::MENU::LowEndPCMode);
		UIHandler->HelpMarker("GAME:\nDisable all text outlines (contours) on the screen\nand reduce the number of displayed items nearby\n(only display objects that are more than 20 meters from the player).\n\nUI:\nDisable all graphics in the UI and the game to increase performance.", false, false);
		ImGui::Checkbox("DEBUG MODE", &SETTINGS::MENU::DebugMode);
		ImGui::SliderInt("DEBUG MAX RENDER DISTANCE", &SETTINGS::MENU::DebugModeMaxRenderDistance, 0, 20000, "%.0f");
		ImGui::EndChild();
	}
	else if (SETTINGS::MENU::activeMenuTab == 6) //-> BEACON TAB
	{
		ImGui::BeginChild("SOT_EXTERNAL_TOOL_BEACON_TAB", ImVec2(835, 445), true);
		UIHandler->UIChildHeaderSingle("PLAYER'S BEACONS SETTINGS", false, 835);

		(SETTINGS::TOOLS::UTILITY::BEACON::firstBeaconEnabled) ? ImGui::Text(u8"ENABLED - FIRST BEACON » LOCATION: x: %.0f, y: %.0f, z: %.0f", SETTINGS::TOOLS::UTILITY::BEACON::firstBeaconLocation[0], SETTINGS::TOOLS::UTILITY::BEACON::firstBeaconLocation[1], SETTINGS::TOOLS::UTILITY::BEACON::firstBeaconLocation[2]) : ImGui::Text("DISABLED - FIRST BEACON");
		if (ImGui::Button("CREATE 1ST BEACON", { 175, 20 }))
			UIHandler->utilityBeacon(1, false);
		UIHandler->spaceBetweenElements(5.f, 0.f);
		if (ImGui::Button("F1", { 75, 20 }))
			UIHandler->utilityBeaconSetKey(1);
		UIHandler->HelpMarker("To assign the selected key to the function of creating this beacon,\npress the button next to it and then the selected key on the keyboard.", false, false);
		UIHandler->spaceBetweenElements(5.f, 0.f);
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2.f);
		ImGui::PushItemWidth(250);
		ImGui::InputText("1ST BEACON NAME", SETTINGS::TOOLS::UTILITY::BEACON::firstBeaconName, 32);
		ImGui::Dummy(ImVec2(0.0f, 1.f));
		if (ImGui::Button("REMOVE 1ST BEACON", { 175, 20 }))
			UIHandler->utilityBeacon(1, true);UIHandler->spaceBetweenElements(5.f, 0.f);
		if (ImGui::Button("NUM1", { 75, 20 }))
			UIHandler->utilityBeaconSetKey(1);
		UIHandler->HelpMarker("To assign the selected key to the function of removing this beacon,\npress the button next to it and then the selected key on the keyboard.", false, false);
		UIHandler->spaceBetweenElements(5.f, 0.f);
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2.f);
		ImGui::ColorEdit4("1ST BEACON COLOR", (float*)&SETTINGS::TOOLS::UTILITY::BEACON::firstBeaconColor);
		ImGui::PopItemWidth();
		ImGui::Dummy(ImVec2(0.0f, 5.f));

		(SETTINGS::TOOLS::UTILITY::BEACON::secondBeaconEnabled) ? ImGui::Text(u8"ENABLED - SECOND BEACON » LOCATION: x: %.0f, y: %.0f, z: %.0f", SETTINGS::TOOLS::UTILITY::BEACON::secondBeaconLocation[0], SETTINGS::TOOLS::UTILITY::BEACON::secondBeaconLocation[1], SETTINGS::TOOLS::UTILITY::BEACON::secondBeaconLocation[2]) : ImGui::Text("DISABLED - SECOND BEACON");
		if (ImGui::Button("CREATE 2ND BEACON", { 175, 20 }))
			UIHandler->utilityBeacon(2, false);
		UIHandler->spaceBetweenElements(5.f, 0.f);
		if (ImGui::Button("F2", { 75, 20 }))
			UIHandler->utilityBeaconSetKey(2);
		UIHandler->HelpMarker("To assign the selected key to the function of creating this beacon,\npress the button next to it and then the selected key on the keyboard.", false, false);
		UIHandler->spaceBetweenElements(5.f, 0.f);
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2.f);
		ImGui::PushItemWidth(250);
		ImGui::InputText("2ND BEACON NAME", SETTINGS::TOOLS::UTILITY::BEACON::secondBeaconName, 32);
		ImGui::Dummy(ImVec2(0.0f, 1.f));
		if (ImGui::Button("REMOVE 2ND BEACON", { 175, 20 }))
			UIHandler->utilityBeacon(2, true);
		UIHandler->spaceBetweenElements(5.f, 0.f);
		if (ImGui::Button("NUM2", { 75, 20 }))
			UIHandler->utilityBeaconSetKey(2);
		UIHandler->HelpMarker("To assign the selected key to the function of removing this beacon,\npress the button next to it and then the selected key on the keyboard.", false, false);
		UIHandler->spaceBetweenElements(5.f, 0.f);
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2.f);
		ImGui::ColorEdit4("2ND BEACON COLOR", (float*)&SETTINGS::TOOLS::UTILITY::BEACON::secondBeaconColor);
		ImGui::PopItemWidth();
		ImGui::Dummy(ImVec2(0.0f, 5.f));

		(SETTINGS::TOOLS::UTILITY::BEACON::thirdBeaconEnabled) ? ImGui::Text(u8"ENABLED - THIRD BEACON » LOCATION: x: %.0f, y: %.0f, z: %.0f", SETTINGS::TOOLS::UTILITY::BEACON::thirdBeaconLocation[0], SETTINGS::TOOLS::UTILITY::BEACON::thirdBeaconLocation[1], SETTINGS::TOOLS::UTILITY::BEACON::thirdBeaconLocation[2]) : ImGui::Text("DISABLED - THIRD BEACON");
		if (ImGui::Button("CREATE 3RD BEACON", { 175, 20 }))
			UIHandler->utilityBeacon(3, false);
		UIHandler->spaceBetweenElements(5.f, 0.f);
		if (ImGui::Button("F3", { 75, 20 }))
			UIHandler->utilityBeaconSetKey(3);
		UIHandler->HelpMarker("To assign the selected key to the function of creating this beacon,\npress the button next to it and then the selected key on the keyboard.", false, false);
		UIHandler->spaceBetweenElements(5.f, 0.f);
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2.f);
		ImGui::PushItemWidth(250);
		ImGui::InputText("3RD BEACON NAME", SETTINGS::TOOLS::UTILITY::BEACON::thirdBeaconName, 32);
		ImGui::Dummy(ImVec2(0.0f, 1.f));
		if (ImGui::Button("REMOVE 3RD BEACON", { 175, 20 }))
			UIHandler->utilityBeacon(3, true);
		UIHandler->spaceBetweenElements(5.f, 0.f);
		if (ImGui::Button("NUM3", { 75, 20 }))
			UIHandler->utilityBeaconSetKey(3);
		UIHandler->HelpMarker("To assign the selected key to the function of removing this beacon,\npress the button next to it and then the selected key on the keyboard.", false, false);
		UIHandler->spaceBetweenElements(5.f, 0.f);
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2.f);
		ImGui::ColorEdit4("3RD BEACON COLOR", (float*)&SETTINGS::TOOLS::UTILITY::BEACON::thirdBeaconColor);
		ImGui::PopItemWidth();
		ImGui::Dummy(ImVec2(0.0f, 5.f));

		(SETTINGS::TOOLS::UTILITY::BEACON::fourthBeaconEnabled) ? ImGui::Text(u8"ENABLED - FOURTH BEACON » LOCATION: x: %.0f, y: %.0f, z: %.0f", SETTINGS::TOOLS::UTILITY::BEACON::fourthBeaconLocation[0], SETTINGS::TOOLS::UTILITY::BEACON::fourthBeaconLocation[1], SETTINGS::TOOLS::UTILITY::BEACON::fourthBeaconLocation[2]) : ImGui::Text("DISABLED - FOURTH BEACON");
		if (ImGui::Button("CREATE 4TH BEACON", { 175, 20 }))
			UIHandler->utilityBeacon(4, false);
		UIHandler->spaceBetweenElements(5.f, 0.f);
		if (ImGui::Button("F4", { 75, 20 }))
			UIHandler->utilityBeaconSetKey(4);
		UIHandler->HelpMarker("To assign the selected key to the function of creating this beacon,\npress the button next to it and then the selected key on the keyboard.", false, false);
		UIHandler->spaceBetweenElements(5.f, 0.f);
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2.f);
		ImGui::PushItemWidth(250);
		ImGui::InputText("4TH BEACON NAME", SETTINGS::TOOLS::UTILITY::BEACON::fourthBeaconName, 32);
		ImGui::Dummy(ImVec2(0.0f, 1.f));
		if (ImGui::Button("REMOVE 4TH BEACON", { 175, 20 }))
			UIHandler->utilityBeacon(4, true);
		UIHandler->spaceBetweenElements(5.f, 0.f);
		if (ImGui::Button("NUM4", { 75, 20 }))
			UIHandler->utilityBeaconSetKey(4);
		UIHandler->HelpMarker("To assign the selected key to the function of removing this beacon,\npress the button next to it and then the selected key on the keyboard.", false, false);
		UIHandler->spaceBetweenElements(5.f, 0.f);
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2.f);
		ImGui::ColorEdit4("4TH BEACON COLOR", (float*)&SETTINGS::TOOLS::UTILITY::BEACON::fourthBeaconColor);
		ImGui::PopItemWidth();
		ImGui::Dummy(ImVec2(0.0f, 5.f));

		(SETTINGS::TOOLS::UTILITY::BEACON::fifthBeaconEnabled) ? ImGui::Text(u8"ENABLED - FIFTH BEACON » LOCATION: x: %.0f, y: %.0f, z: %.0f", SETTINGS::TOOLS::UTILITY::BEACON::fifthBeaconLocation[0], SETTINGS::TOOLS::UTILITY::BEACON::fifthBeaconLocation[1], SETTINGS::TOOLS::UTILITY::BEACON::fifthBeaconLocation[2]) : ImGui::Text("DISABLED - FIFTH BEACON");
		if (ImGui::Button("CREATE 5TH BEACON", { 175, 20 }))
			UIHandler->utilityBeacon(5, false);
		UIHandler->spaceBetweenElements(5.f, 0.f);
		if (ImGui::Button("F5", { 75, 20 }))
			UIHandler->utilityBeaconSetKey(5);
		UIHandler->HelpMarker("To assign the selected key to the function of creating this beacon,\npress the button next to it and then the selected key on the keyboard.", false, false);
		UIHandler->spaceBetweenElements(5.f, 0.f);
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2.f);
		ImGui::PushItemWidth(250);
		ImGui::InputText("5TH BEACON NAME", SETTINGS::TOOLS::UTILITY::BEACON::fifthBeaconName, 32);
		ImGui::Dummy(ImVec2(0.0f, 1.f));
		if (ImGui::Button("REMOVE 5TH BEACON", { 175, 20 }))
			UIHandler->utilityBeacon(5, true);
		UIHandler->spaceBetweenElements(5.f, 0.f);
		if (ImGui::Button("NUM5", { 75, 20 }))
			UIHandler->utilityBeaconSetKey(5);
		UIHandler->HelpMarker("To assign the selected key to the function of removing this beacon,\npress the button next to it and then the selected key on the keyboard.", false, false);
		UIHandler->spaceBetweenElements(5.f, 0.f);
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2.f);
		ImGui::ColorEdit4("5TH BEACON COLOR", (float*)&SETTINGS::TOOLS::UTILITY::BEACON::fifthBeaconColor);
		ImGui::PopItemWidth();

		ImGui::EndChild();
	}

	//
	ImGui::End();
	ImGui::Render();
}

void UpdateOverlay()
{
	while (true)
	{
		if (GLOBAL_DEFINITION::tWnd == GetForegroundWindow()) { }

		if (GetAsyncKeyState(VK_END)) //-> PANIC KEY
			ExitProcess(1);

		if (GetAsyncKeyState(VK_INSERT)) //-> MENU KEY
		{
			if (!GLOBAL_DEFINITION::MenuShown)
			{
				long winlong = GetWindowLong(GLOBAL_DEFINITION::hWnd, GWL_EXSTYLE);

				if (winlong != WS_EX_TOPMOST | WS_EX_LAYERED)
					SetWindowLong(GLOBAL_DEFINITION::hWnd, GWL_EXSTYLE, WS_EX_TOPMOST | WS_EX_LAYERED);
				
				SetForegroundWindow(GLOBAL_DEFINITION::hWnd);
			}
			else if (GLOBAL_DEFINITION::MenuShown)
			{
				long winlong = GetWindowLong(GLOBAL_DEFINITION::hWnd, GWL_EXSTYLE);

				if (winlong != WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TRANSPARENT)
					SetWindowLong(GLOBAL_DEFINITION::hWnd, GWL_EXSTYLE, WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TRANSPARENT);

				SetForegroundWindow(GLOBAL_DEFINITION::tWnd);
			}

			GLOBAL_DEFINITION::MenuShown = !GLOBAL_DEFINITION::MenuShown;

			while (GetAsyncKeyState(0x2D)) {}
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(32));
	}
}
