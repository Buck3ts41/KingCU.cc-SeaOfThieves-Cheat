#include "../Core/SOTStuff.h"

#include <clocale>
#include <cstdlib>

cSOT* SOT = new cSOT();

offsets Offsets;

Vector3 USceneComponent::GetPosition()
{
	return this->transform.Translation;
}

Vector3 USceneComponent::GetRotation()
{
	return Vector3(this->transform.Rotation.X, this->transform.Rotation.Y, this->transform.Rotation.Z);
}

int AActor::GetID()
{
	return *(int*)(__pad0x0 + Offsets.AActor.actorId);
}

USceneComponent AActor::GetRootComponent()
{
	return MemoryManager->Read<USceneComponent>(*(uintptr_t*)(__pad0x0 + Offsets.AActor.rootComponent));
}

APlayerState AActor::GetPlayerState()
{
	return MemoryManager->Read<APlayerState>(*(uintptr_t*)(__pad0x0 + Offsets.AActor.PlayerState));
}

UWieldedItemComponent AActor::GetWieldedItemComponent()
{
	return MemoryManager->Read < UWieldedItemComponent>(*(uintptr_t*)(__pad0x0 + Offsets.AActor.WieldedItemComponent));
}

UHealthComponent AActor::GetHealthComponent()
{
	return MemoryManager->Read< UHealthComponent>(*(uintptr_t*)(__pad0x0 + Offsets.AActor.HealthComponent));
}

UDrowningComponent ACharacter::GetDrowningComponent()
{
	return MemoryManager->Read< UDrowningComponent>(*(uintptr_t*)(__pad0x0 + Offsets.AActor.DrowningComponent));
}

TArray<Chunk*> ULevel::GetActors() const
{
	return this->m_Actors;
}

Vector3 APlayerCameraManager::GetCameraPosition()
{
	return this->position;
}

Vector3 APlayerCameraManager::GetCameraRotation()
{
	return this->rotation;
}

float APlayerCameraManager::GetCameraFOV()
{
	return this->fov;
}

AActor APlayerController::GetActor()
{
	return MemoryManager->Read<AActor>(*(uintptr_t*)(__pad0x0 + Offsets.APlayerController.Pawn));
}

ACharacter APlayerController::GetCharacter()
{
	return MemoryManager->Read<ACharacter>(*(uintptr_t*)(__pad0x0 + Offsets.APlayerController.Character));
}

APlayerCameraManager APlayerController::GetCameraManager()
{
	return MemoryManager->Read<APlayerCameraManager>(*(uintptr_t*)(__pad0x0 + Offsets.APlayerController.CameraManager));
}

APlayerController ULocalPlayer::GetPlayerController()
{
	return MemoryManager->Read<APlayerController>(*(uintptr_t*)(__pad0x0 + Offsets.ULocalPlayer.PlayerController));
}

ULocalPlayer UGameInstance::GetLocalPlayer()
{
	return MemoryManager->Read<ULocalPlayer>(MemoryManager->Read<uintptr_t>(*(uintptr_t*)(__pad0x0 + Offsets.UGameInstance.LocalPlayers)));
}

ULevel cUWorld::GetLevel() const
{
	return MemoryManager->Read<ULevel>(*(uintptr_t*)(__pad0x0 + Offsets.UWorld.PersistentLevel));
}

UGameInstance cUWorld::GetGameInstance() const
{
	return MemoryManager->Read<UGameInstance>(*(uintptr_t*)(__pad0x0 + Offsets.UWorld.OwningGameInstance));
}

TArray<struct FAlliance> AAllianceService::GetAlliances()
{
	return this->Alliances;
}

TArray<struct FCrew> ACrewService::GetCrews()
{
	return *(TArray<struct FCrew>*)(__pad0x0 + Offsets.ACrewService.Crews);
}

TArray<class APlayerState*> FCrew::GetPlayers()
{
	return this->Players;
}

std::string FCrew::GetShipType()
{

	switch (this->maxPlayersOnShip)
	{
	case 2:
		return "Sloop";
		break;
	case 3:
		return "Brigantine";
		break;
	case 4:
		return "Galleon";
		break;
	default:
		return "";
		break;
	}
}

FGuid FCrew::GetCrewID()
{
	return this->CrewID;
}

std::wstring APlayerState::GetName()
{
	return MemoryManager->Read<textx>(*(uintptr_t*)(__pad0x0 + Offsets.APlayerState.PlayerName)).word;
}

int UHealthComponent::GetHealth()
{
	return this->health;
}

int UHealthComponent::GetMaxHealth()
{
	return this->maxHealth;
}

float UDrowningComponent::GetOxygenLevel()
{
	return this->oxygenLevel;
}

FGuid UCrewOwnershipComponent::GetCrewId()
{
	return *(FGuid*)(__pad0x0 + Offsets.UCrewOwnershipComponent.CrewId);
}

UCrewOwnershipComponent AShip::GetCrewOwnershipComponent()
{
	return MemoryManager->Read<UCrewOwnershipComponent>(*(uintptr_t*)(__pad0x0 + Offsets.AShip.CrewOwnershipComponent));
}

uintptr_t AShip::GetOwningActor()
{
	return *(uintptr_t*)(__pad0x0 + Offsets.AShip.ShipOwningActor);
}

TArray<struct FXMarksTheSpotMapMark> AXMarksTheSpotMap::GetMarks()
{
	return this->Marks;
}

ABootyItemInfo AItemProxy::GetBootyItemInfo()
{
	return MemoryManager->Read<ABootyItemInfo>(*(uintptr_t*)(__pad0x0 + Offsets.AItemProxy.AItemInfo));
}

UItemDesc ABootyItemInfo::GetItemDesc()
{
	return MemoryManager->Read<UItemDesc>(*(uintptr_t*)(__pad0x0 + Offsets.AItemInfo.UItemDesc));
}

int ABootyItemInfo::GetBootyType()
{
	return *(int*)(__pad0x0 + Offsets.ABootyItemInfo.BootyType);
}

int ABootyItemInfo::GetRareityId()
{
	return *(int*)(__pad0x0 + Offsets.ABootyItemInfo.Rarity);
}

std::wstring UItemDesc::GetName()
{
	return MemoryManager->Read<textx>(MemoryManager->Read<uintptr_t>(this->m_pName)).word;
}

AWieldableItem UWieldedItemComponent::GetWieldedItem()
{
	return MemoryManager->Read <AWieldableItem>(*(uintptr_t*)(__pad0x0 + Offsets.UWieldedItemComponent.WieldedItem));
}

AItemInfo AWieldableItem::GetItemInfo()
{
	return  MemoryManager->Read <AItemInfo>(*(uintptr_t*)(__pad0x0 + Offsets.AWieldableItem.ItemInfo));
}

UItemDesc AItemInfo::GetItemDesc()
{
	return MemoryManager->Read <UItemDesc>(*(uintptr_t*)(__pad0x0 + Offsets.AItemInfo.UItemDesc));
}

float ACannon::GetTimePerFire()
{
	return *(float*)(__pad0x0 + Offsets.ACannon.TimePerFire);
}

float ACannon::GetProjectileSpeed()
{
	return *(float*)(__pad0x0 + Offsets.ACannon.ProjectileSpeed);
}

float ACannon::GetProjectileGravityScale()
{
	return *(float*)(__pad0x0 + Offsets.ACannon.ProjectileGravityScale);
}

float ACannon::GetServerPitch()
{
	return *(float*)(__pad0x0 + Offsets.ACannon.ServerPitch);
}

Vector2 AMapTable::GetServerCenter()
{
	return *(Vector2*)(__pad0x0 + Offsets.AMapTable.ServerCenter);
}

TArray<struct Vector2> AMapTable::GetMapPins()
{
	return *(TArray<struct Vector2>*)(__pad0x0 + Offsets.AMapTable.MapPins);
}

TArray<class FWorldMapShipLocation> AMapTable::GetTrackedShips()
{
	return *(TArray<class FWorldMapShipLocation>*)(__pad0x0 + Offsets.AMapTable.TrackedShips);
}

TArray<struct Vector3> AMapTable::GetTrackedBootyItemLocations()
{
	return *(TArray<struct Vector3>*)(__pad0x0 + Offsets.AMapTable.MapPins + 0x20);
}

TArray<struct FIsland> AIslandService::GetIslandArray()
{
	return this->IslandArray;
}

UIslandDataAsset AIslandService::GetIslandDataAsset()
{
	return MemoryManager->Read<UIslandDataAsset>(this->m_pIslandDataAsset);
}

FGuid FWorldMapShipLocation::GetCrewId()
{
	return this->crewId;
}

UObject FWorldMapShipLocation::GetUObject()
{
	return MemoryManager->Read<UObject>(this->m_pUObject);
}

Vector2 FWorldMapShipLocation::GetLocation()
{
	return this->m_Location;
}

std::wstring AFauna::GetName()
{
	return MemoryManager->Read<textx>(MemoryManager->Read<uintptr_t>(*(uintptr_t*)(__pad0x0 + Offsets.AFauna.Name))).word;
}

TArray<class UIslandDataAssetEntry> UIslandDataAsset::GetIslandDataAssetEntry()
{
	return (this->IslandDataEntries);
}

int UIslandDataAssetEntry::GetNameID()
{
	return this->IslandNameId;
}

std::wstring UIslandDataAssetEntry::GetName()
{
	return MemoryManager->Read<textx>(MemoryManager->Read<uintptr_t>(this->IslandName + 0x28)).word;
}

TArray<class ULevel*> AllWorlds::GetAllLevels()
{
	return this->AllLevels;
}

