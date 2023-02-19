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
		int Character = 992;
		int CameraManager = 1112;
		int ControlRotation = 772;
	}APlayerController;

	struct AActor
	{
		int actorId = 24;
		int rootComponent = 360;
		int PlayerState = 1000;
		int WieldedItemComponent = 2096;
		int HealthComponent = 2200;
		int DrowningComponent = 3472;
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
		int AItemInfo = 1816;
	}AItemProxy;

	struct AItemInfo
	{
		int UItemDesc = 1088;
	}AItemInfo;

	struct ABootyItemInfo
	{
		int BootyType = 1344;
		int Rarity = 1716;
	}ABootyItemInfo;

	struct AShip
	{
		int CrewOwnershipComponent = 1968;
		int ShipInternalWaterComponent = 1568;
		int ShipOwningActor = 1000;
	}AShip;

	struct ACannon
	{
		int TimePerFire = 1464;
		int ProjectileSpeed = 1468;
		int ProjectileGravityScale = 1472;
		int ServerPitch = 1976;
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
		int TrackedShips = 1272;
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
		int ItemInfo = 1816;
	}AWieldableItem;
};
extern offsets Offsets;