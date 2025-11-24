// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/TurretWorldManager.h"

#include "C++Scripts/Enemies/TurretBase.h"

void UTurretWorldManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	UE_LOG(LogTemp, Log, TEXT("TurretManager Initialized"));
}

void UTurretWorldManager::Deinitialize()
{
	RegisteredTurrets.Empty();
	Super::Deinitialize();
	UE_LOG(LogTemp,Log, TEXT("TurretManager Deinitialized"));
}

void UTurretWorldManager::RegisterTurret(ATurretBase* Turret)
{
	if (Turret && !RegisteredTurrets.Contains(Turret))
	{
		RegisteredTurrets.Add(Turret);
		UE_LOG(LogTemp, Log, TEXT("Turret Registered: %s"), *Turret->GetName());
	}
}

void UTurretWorldManager::UnRegisterTurret(ATurretBase* Turret)
{
	if (Turret)
	{
		RegisteredTurrets.Remove(Turret);
		UE_LOG(LogTemp, Log, TEXT("Turret Unregistered: %s"), *Turret->GetName());	
	}
}

void UTurretWorldManager::DisableAllTurrets()
{
	for (auto& TurretWeakPtr : RegisteredTurrets)
	{
		if (ATurretBase* Turret = TurretWeakPtr.Get())
		{
			Turret->SetTurretEnabled(false);
		}
	}
	UE_LOG(LogTemp, Log, TEXT("All Turrets Disabled"));
}
