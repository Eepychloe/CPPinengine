// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MenuController.generated.h"

class UMenuStyleDA;
class UMainMenu;
/**
 * 
 */
UCLASS()
class GAMJAM25_API AMenuController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = UI)
	TSubclassOf<UMainMenu> MainMenuClass;

	UPROPERTY(EditDefaultsOnly, Category = Flow)
	TObjectPtr<UMenuStyleDA> MenuFlow;

	UPROPERTY()
	TObjectPtr<UMainMenu> MainMenu;

	UFUNCTION()
	void HandleOnPlayGame();

	UFUNCTION()
	void HandleOnQuitGame();
};
