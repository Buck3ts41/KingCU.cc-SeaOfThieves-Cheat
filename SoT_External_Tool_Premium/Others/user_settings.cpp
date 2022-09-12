#include "../Others/user_settings.h"

namespace SETTINGS
{
	namespace MENU
	{
		bool LowEndPCMode = false;

		bool DebugMode = false;
		int DebugModeMaxRenderDistance = 10;

		//-> GENERAL MENU
		const char* menuTabs[] = { "GENERAL", "TREASURES ESP", "OBJECTS ESP", "AIMHELPER", "MISCELLANEOUS", "UTILITY", "BEACONS" };
		int activeMenuTab = 0;

		//-> TREASURES ESP MENU
		const char* menuTabs_treasures[] = { "GENERAL", "COMMON", "RARE", "EPIC", "MYTHICAL", "LEGENDARY", "MERCHANT", "LORE BOOKS", "QUESTS", "OTHERS" };
		int activeMenuTab_treasures = 0;

		//-> OBJECTS ESP MENU
		const char* menuTabs_objects[] = { "GENERAL", "PLAYERS", "PLAYERS SHIPS", "SKELETONS", "AI SHIPS", "ANIMALS", "ISLANDS" };
		int activeMenuTab_objects = 0;
	};

	namespace TOOLS
	{
		namespace UTILITY
		{
			namespace CROSSHAIR
			{
				bool crosshairEnabled = true;
				const char* crosshairGradientType = "HORIZONTAL";
				const char* crosshairGradientTypes[] = { "HORIZONTAL", "VERTICAL" };
				float crosshairSize = 5.f;
				float crosshairThickness = 2.f;

				float crosshairColor[] = { 1.00f, 1.00f, 1.00f, 1.00f };

				//-> Gradient Crosshair
				bool crosshairGradient = false;
				float crosshairStartColor[] = { 1.00f, 1.00f, 1.00f, 1.00f };
				float crosshairEndColor[] = { 1.00f, 1.00f, 1.00f, 1.00f };
			};

			namespace COMPASS
			{
				bool compassEnabled = true;
				bool compassFullName = true;
				bool compassSpeed = false;
				int compassSize = 3;
				float compassColor[] = { 1.00f, 1.00f, 1.00f, 1.00f };
			};

			/*
			-> Rewrite to vector
			-> make temp vector for settings and normal one for reading data in real time without fps drops
			*/
			namespace BEACON
			{
				//-> FIRST BEACON
				bool firstBeaconEnabled = false;
				char firstBeaconName[32] = "First Beacon Name";
				float firstBeaconLocation[] = { 0.00f, 0.00f, 0.00f };
				float firstBeaconColor[] = { 1.00f, 1.00f, 1.00f, 1.00f };

				//-> SECOND BEACON
				bool secondBeaconEnabled = false;
				char secondBeaconName[32] = "Second Beacon Name";
				float secondBeaconLocation[] = { 0.00f, 0.00f, 0.00f };
				float secondBeaconColor[] = { 1.00f, 1.00f, 1.00f, 1.00f };

				//-> THIRD BEACON
				bool thirdBeaconEnabled = false;
				char thirdBeaconName[32] = "Third Beacon Name";
				float thirdBeaconLocation[] = { 0.00f, 0.00f, 0.00f };
				float thirdBeaconColor[] = { 1.00f, 1.00f, 1.00f, 1.00f };

				//-> FOURTH BEACON
				bool fourthBeaconEnabled = false;
				char fourthBeaconName[32] = "Fourth Beacon Name";
				float fourthBeaconLocation[] = { 0.00f, 0.00f, 0.00f };
				float fourthBeaconColor[] = { 1.00f, 1.00f, 1.00f, 1.00f };

				//-> FIFTH BEACON
				bool fifthBeaconEnabled = false;
				char fifthBeaconName[32] = "Fifth Beacon Name";
				float fifthBeaconLocation[] = { 0.00f, 0.00f, 0.00f };
				float fifthBeaconColor[] = { 1.00f, 1.00f, 1.00f, 1.00f };
			};

			namespace OXYGEN
			{
				bool oxygenEnabled = false;
				float oxygenColor[] = { 0.329f, 0.666f, 0.921f, 1.00f };
				bool oxygenWarning = false;
				float oxygenWarningColor[] = { 0.858f, 0.266f, 0.266f, 1.00f };
			};
		};

		namespace TREASURES_ESP
		{
			namespace GENERAL
			{
				bool treasuresESPEnabled = true;
				bool treasuresGeneralColors = true;
				float treasuresCommonColor[] = { 0.693f, 0.693f, 0.693f, 1.00f };
				float treasuresRareColor[] = { 0.138f, 0.446f, 0.740f, 1.00f };
				float treasuresEpicColor[] = { 0.420f, 0.199f, 0.823f, 1.00f };
				float treasuresMythicalColor[] = { 0.893f, 0.162f, 0.096f, 1.00f };
				float treasuresLegendaryColor[] = { 0.888f, 0.470f, 0.132f, 1.00f };
				float treasuresMerchantColor[] = { 0.637f, 0.674f, 0.508f, 1.00f };
				float treasuresLoreBooksColor[] = { 0.578f, 0.712f, 0.189f, 1.00f };
				float treasuresQuestsColor[] = { 0.220f, 0.777f, 0.693f, 1.00f };
				float treasuresOthersColor[] = { 0.753f, 0.753f, 0.753f, 1.00f };

				bool treasuresGeneralDistance = true;
				int treasuresGeneralDistanceLow = 150;
				int treasuresGeneralDistanceMedium = 500;

				const char* treasuresCommon[] = { "Mysterious Coral Vessel", "Foul Coral Skull", "Skull of the Damned", "Foul Skull", "Coral Castaway Chest", "Ashen Castaway Chest", "Wrecked Castaway Chest", "Vault Castaway Chest", "Castaway Chest", "Athena's Crate", "Roaring Goblet" };
				int treasuresCommonActiveTab = 0;
			};
		};

		namespace OBJECTS_ESP
		{
			namespace PLAYERS
			{
				namespace ALLIES
				{
					bool showAllies = true;
					bool showName = true;
					float nameColor[] = { 0.638f, 0.907f, 0.451f, 1.00f };
					bool showHealthBar = true;
					bool showHealthPoints = true;
					bool showWhenIsDown = true;
					float downColor[] = { 0.949f, 0.031f, 0.031f, 1.00f };
					const char* tracelinesType = "DISABLED";
					const char* tracelinesTypes[] = { "DISABLED", "CROSSHAIR", "TOP OF SCREEN", "BOTTOM OF SCREEN" };
					float tracelineColor[] = { 0.045f, 0.372f, 0.121f, 1.00f };
					const char* boxType = "2D CORNERS BOX";
					const char* boxTypes[] = { "DISABLED", "2D FULL BOX", "2D FULL BOX - BLACK OUTLINE", "2D FULL BOX - WHITE OUTLINE", "2D CORNERS BOX", "2D CORNERS BOX - BLACK OUTLINE", "2D CORNERS BOX - WHITE OUTLINE" };
					float boxColor[] = { 0.153f, 0.670f, 0.390f, 1.00f };
					bool showDistance = true;
					float distanceColor[] = { 1.00f, 1.00f, 1.00f, 1.00f };
					bool showWeapon = true;
					float weaponColor[] = { 1.00f, 1.00f, 1.00f, 1.00f };
				};

				namespace ENEMIES
				{
					bool showEnemies = true;
					bool showName = true;
					float nameColor[] = { 0.907f, 0.515f, 0.451f, 1.00f };
					bool showHealthBar = true;
					bool showHealthPoints = true;
					bool showWhenIsDown = true;
					float downColor[] = { 0.108f, 0.833f, 0.358f, 1.00f };
					const char* tracelinesType = "DISABLED";
					const char* tracelinesTypes[] = { "DISABLED", "CROSSHAIR", "TOP OF SCREEN", "BOTTOM OF SCREEN" };
					float tracelineColor[] = { 0.414f, 0.090f, 0.090f, 1.00f };
					const char* boxType = "2D CORNERS BOX";
					const char* boxTypes[] = { "DISABLED", "2D FULL BOX", "2D FULL BOX - BLACK OUTLINE", "2D FULL BOX - WHITE OUTLINE", "2D CORNERS BOX", "2D CORNERS BOX - BLACK OUTLINE", "2D CORNERS BOX - WHITE OUTLINE" };
					float boxColor[] = { 0.874f, 0.206f, 0.187f, 1.000f };
					bool showDistance = true;
					float distanceColor[] = { 1.00f, 1.00f, 1.00f, 1.00f };
					bool showWeapon = true;
					float weaponColor[] = { 1.00f, 1.00f, 1.00f, 1.00f };
				};
			};

			namespace SHIPS
			{
				namespace ALLY_SHIPS
				{
					bool showShips = true;
					float Color[] = { 0.638f, 0.907f, 0.451f, 1.00f };
					bool Distance = false;
					int MaxDistanceToRender = 0;
					bool Health = false;
					bool Water = false;
					bool Velocity = true;
					bool DamageZones = false;
					float DamageZonesColor[] = { 0.907f, 0.515f, 0.451f, 1.00f };
					int DamageZonesMaxDistance = 0;
					bool ShowAmmo = false;

				};

				namespace ENEMY_SHIPS
				{
					bool showShips = true;
					bool ShowEmissaryFlagInName = true;
					bool UniqueColorsForCrews = true;
					float AzureScoutColor[] = { 0.246f, 0.853f, 0.920f, 1.00f };
					float RegalHoundColor[] = { 0.920f, 0.246f, 0.246f, 1.00f };
					float LuckyRoverColor[] = { 0.033f, 0.794f, 0.343f, 1.00f };
					float FlamingJackalColor[] = { 0.789f, 0.527f, 0.013f, 1.00f };
					float GoldenChaserColor[] = { 0.862f, 0.880f, 0.099f, 1.00f };
					float Color[] = { 0.907f, 0.515f, 0.451f, 1.00f };
					bool Distance = true;
					int MaxDistanceToRender = 0;
					bool Health = false;
					bool Water = false;
					bool Velocity = true;
					bool DamageZones = false;
					float DamageZonesColor[] = { 0.638f, 0.907f, 0.451f, 1.00f };
					int DamageZonesMaxDistance = 0;
				};

				namespace SHIP_WRECKS //todo
				{
					bool showShipWrecks = true;
					float shipWrecksColor[] = { 1.00f, 1.00f, 1.00f, 1.00f };
					float shipWrecksMaxDistanceToRender = 0.f;
					bool shipWrecksDistance = false;
				};

				namespace ROWBOATS //todo
				{
					bool showRowboats = true;
					float rowboatColor[] = { 1.00f, 1.00f, 1.00f, 1.00f };
					float rowboatMaxDistanceToRender = 0.f;
					bool rowboatDistance = false;
				};
			};
		};
	};
};