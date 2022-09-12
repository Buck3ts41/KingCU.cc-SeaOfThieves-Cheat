#pragma once
class offsets {
public:
	struct UWorld
	{
		int PersistentLevel = 48;
		int OwningGameInstance = 448;
	}UWorld;

	struct UGameInstance
	{
		int LocalPlayers = 56;
	}UGameInstance;

	struct UPlayer
	{
		int PlayerController = 48;
	}ULocalPlayer;

	struct ULevel
	{
		int AActor = 0xA0;
	}ULevel;

	struct APlayerController
	{
		int Pawn = 976;
		int Character = 0x3E8;
		int CameraManager = 1112;
		int ControlRotation = 772;
	}APlayerController;

	struct AActor
	{
		int actorId = 24;
		int rootComponent = 360;
		int PlayerState = 1000;
		int WieldedItemComponent = 2096;
		int HealthComponent = 2136;
		int DrowningComponent = 0xCA8;
	}AActor;

	struct APlayerState
	{
		int PlayerName = 976;
	}APlayerState;

	struct APlayerCameraManager
	{
		int CameraCache = 1088;
	}APlayerCameraManager;

	struct AItemProxy
	{
		int AItemInfo = 1472;
	}AItemProxy;

	struct AItemInfo
	{
		int UItemDesc = 1088;
	}AItemInfo;

	struct ABootyItemInfo
	{
		int BootyType = 1336;
		int Rarity = 1708;
	}ABootyItemInfo;

	struct AShip
	{
		int CrewOwnershipComponent = 1936;
		int ShipInternalWaterComponent = 0x05E0;
		int ShipOwningActor = 0x3E0;
	}AShip;

	struct ACannon
	{
		int TimePerFire = 0x5A0;
		int ProjectileSpeed = 0x5A4;
		int ProjectileGravityScale = 0x5A8;
		int ServerPitch = 0x754;
	}ACannon;

	struct UCrewOwnershipComponent
	{
		int CrewId = 212;
	}UCrewOwnershipComponent;

	struct AFauna
	{
		int Name = 2072;
	}AFauna;

	struct AMaptTable
	{
		int ServerCenter = 1224;
		int MapPins = 1256;
		int TrackedShips = 1156;
	}AMapTable;

	struct ACrewService
	{
		int Crews = 1184;
	}ACrewService;

	struct UWieldedItemComponent
	{
		int WieldedItem = 744;
	}UWieldedItemComponent;

	struct AWieldableItem
	{
		int ItemInfo = 1800;
	}AWieldableItem;
};
extern offsets Offsets;