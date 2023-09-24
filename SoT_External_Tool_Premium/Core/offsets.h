#pragma once
class offsets {
public:
	struct UWorld
	{
		int PersistentLevel = 0x30;
		int OwningGameInstance = 0x1C0;
	}UWorld;

	struct UGameInstance
	{
		int LocalPlayers = 0x38;
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
		int Pawn = 0x3D0;
		int Character = 0x3E0;
		int CameraManager = 0x458;
		int ControlRotation = 0x304;
	}APlayerController;

	struct AActor
	{
		int actorId = 0x18;
		int rootComponent = 0x168;
		int PlayerState = 0x3E8;
		int WieldedItemComponent = 0x880;
		int HealthComponent = 0x8A8;
		int DrowningComponent = 0xDE8;
	}AActor;

	struct APlayerState
	{
		int PlayerName = 0x3D0;
	}APlayerState;

	struct APlayerCameraManager
	{
		int CameraCache = 0x440;
	}APlayerCameraManager;

	struct AItemProxy
	{
		int AItemInfo = 0x6C8;
	}AItemProxy;

	struct AItemInfo
	{
		int UItemDesc = 0x440;
	}AItemInfo;

	struct ABootyItemInfo
	{
		int BootyType = 0x540;
		int Rarity = 0x6B4;
	}ABootyItemInfo;

	struct AShip
	{
		int CrewOwnershipComponent = 0x7C0;
		int ShipInternalWaterComponent = 0x628;
		int ShipOwningActor = 0x3E8;
	}AShip;

	struct ACannon
	{
		int TimePerFire = 0x5B8;
		int ProjectileSpeed = 0x5BC;
		int ProjectileGravityScale = 0x5C0;
		int ServerPitch = 0x7B8;
	}ACannon;

	struct UCrewOwnershipComponent
	{
		int CrewId = 0xD4;
	}UCrewOwnershipComponent;

	struct AFauna
	{
		int Name = 0x818;
	}AFauna;

	struct AMaptTable
	{
		int ServerCenter = 0x4C0;
		int MapPins = 0x4E0;
		int TrackedShips = 0x4F0;
	}AMapTable;

	struct ACrewService
	{
		int Crews = 0x4A0;
	}ACrewService;

	struct UWieldedItemComponent
	{
		int WieldedItem = 0x2E8;
	}UWieldedItemComponent;

	struct AWieldableItem
	{
		int ItemInfo = 0x758;
	}AWieldableItem;
};
extern offsets Offsets;
