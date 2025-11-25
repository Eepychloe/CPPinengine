// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuController.h"
#include "GameFramework/GameModeBase.h"
#include "MenuGM.generated.h"

/**
 * 
 */
UCLASS()
class GAMJAM25_API AMenuGM : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMenuGM()
	{
		PlayerControllerClass = AMenuController::StaticClass();
		DefaultPawnClass = nullptr;
		HUDClass = nullptr;
	}
};
