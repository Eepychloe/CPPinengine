// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "TurretWorldManager.generated.h"

class ATurretBase;
/**
 * 
 */
UCLASS()
class GAMJAM25_API UTurretWorldManager : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;

	void RegisterTurret(ATurretBase* Turret);
	void UnRegisterTurret(ATurretBase* Turret);

	UFUNCTION(BlueprintCallable)
	void DisableAllTurrets();

private:
	UPROPERTY()
	TArray<TWeakObjectPtr<ATurretBase>> RegisteredTurrets;
};
