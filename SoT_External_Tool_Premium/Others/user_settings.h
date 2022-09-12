#pragma once
#include "../Core/main.h"


namespace SETTINGS
{
	namespace MENU
	{
		extern bool LowEndPCMode;

		extern bool DebugMode;
		extern int DebugModeMaxRenderDistance;

		extern const char* menuTabs[7];
		extern int activeMenuTab;

		extern const char* menuTabs_treasures[10];
		extern int activeMenuTab_treasures;

		extern const char* menuTabs_objects[7];
		extern int activeMenuTab_objects;
	};

	namespace TOOLS
	{
		namespace UTILITY
		{
			namespace CROSSHAIR
			{
				extern bool crosshairEnabled;
				extern float crosshairSize;
				extern float crosshairThickness;
				extern float crosshairColor[];

				extern bool crosshairGradient;
				extern const char* crosshairGradientType;
				extern const char* crosshairGradientTypes[];
				extern float crosshairStartColor[];
				extern float crosshairEndColor[];
			};

			namespace COMPASS
			{
				extern bool compassEnabled;
				extern bool compassFullName;
				extern bool compassSpeed;
				extern int compassSize;
				extern float compassColor[];
			};

			namespace BEACON
			{
				//-> FIRST BEACON
				extern bool firstBeaconEnabled;
				extern char firstBeaconName[32];
				extern float firstBeaconLocation[];
				extern float firstBeaconColor[];

				//-> SECOND BEACON
				extern bool secondBeaconEnabled;
				extern char secondBeaconName[32];
				extern float secondBeaconLocation[];
				extern float secondBeaconColor[];

				//-> THIRD BEACON
				extern bool thirdBeaconEnabled;
				extern char thirdBeaconName[32];
				extern float thirdBeaconLocation[];
				extern float thirdBeaconColor[];

				//-> FOURTH BEACON
				extern bool fourthBeaconEnabled;
				extern char fourthBeaconName[32];
				extern float fourthBeaconLocation[];
				extern float fourthBeaconColor[];

				//-> FIFTH BEACON
				extern bool fifthBeaconEnabled;
				extern char fifthBeaconName[32];
				extern float fifthBeaconLocation[];
				extern float fifthBeaconColor[];
			};

			namespace OXYGEN
			{
				extern bool oxygenEnabled;
				extern float oxygenColor[];
				extern bool oxygenWarning;
				extern float oxygenWarningColor[];
			};
		};

		namespace TREASURES_ESP
		{
			namespace GENERAL
			{
				extern bool treasuresESPEnabled;
				extern bool treasuresGeneralColors;
				extern float treasuresCommonColor[];
				extern float treasuresRareColor[];
				extern float treasuresEpicColor[];
				extern float treasuresMythicalColor[];
				extern float treasuresLegendaryColor[];
				extern float treasuresMerchantColor[];
				extern float treasuresLoreBooksColor[];
				extern float treasuresQuestsColor[];
				extern float treasuresOthersColor[];

				extern bool treasuresGeneralDistance;
				extern int treasuresGeneralDistanceLow;
				extern int treasuresGeneralDistanceMedium;

				extern const char* treasuresCommon[11];
				extern int treasuresCommonActiveTab;
			};
		};

		namespace OBJECTS_ESP
		{
			namespace PLAYERS
			{
				namespace ALLIES
				{
					extern bool showAllies;
					extern bool showName;
					extern float nameColor[];
					extern bool showHealthBar;
					extern bool showHealthPoints;
					extern bool showWhenIsDown;
					extern float downColor[];
					extern const char* tracelinesType;
					extern const char* tracelinesTypes[4];
					extern float tracelineColor[];
					extern const char* boxType;
					extern const char* boxTypes[7];
					extern float boxColor[];
					extern bool showDistance;
					extern float distanceColor[];
					extern bool showWeapon;
					extern float weaponColor[];

				};

				namespace ENEMIES
				{
					extern bool showEnemies;
					extern bool showName;
					extern float nameColor[];
					extern bool showHealthBar;
					extern bool showHealthPoints;
					extern bool showWhenIsDown;
					extern float downColor[];
					extern const char* tracelinesType;
					extern const char* tracelinesTypes[4];
					extern float tracelineColor[];
					extern const char* boxType;
					extern const char* boxTypes[7];
					extern float boxColor[];
					extern bool showDistance;
					extern float distanceColor[];
					extern bool showWeapon;
					extern float weaponColor[];
				};
			};

			namespace SHIPS
			{
				namespace ALLY_SHIPS
				{
					extern bool showShips;
					extern int MaxDistanceToRender;
					extern float Color[];
					extern bool Distance;
					extern bool Health;
					extern bool Water;
					extern bool Velocity;
					extern bool DamageZones;
					extern float DamageZonesColor[];
					extern int DamageZonesMaxDistance;
					extern bool ShowAmmo;
				};

				namespace ENEMY_SHIPS
				{
					extern bool showShips;
					extern bool ShowEmissaryFlagInName;
					extern bool UniqueColorsForCrews;
					extern float AzureScoutColor[];
					extern float RegalHoundColor[];
					extern float LuckyRoverColor[];
					extern float FlamingJackalColor[];
					extern float GoldenChaserColor[];
					extern float Color[];
					extern int MaxDistanceToRender;
					extern bool Distance;
					extern bool Health;
					extern bool Water;
					extern bool Velocity;
					extern bool DamageZones;
					extern float DamageZonesColor[];
					extern int DamageZonesMaxDistance;
				};

				namespace ROWBOATS
				{
					extern bool showRowboats;
					extern float rowboatColor[];
					extern float rowboatMaxDistanceToRender;
					extern bool rowboatDistance;
				}
			};
		};
	};
};
