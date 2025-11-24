// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IADataConfig.h"
#include "GameFramework/PlayerController.h"
#include "InputMappingContext.h"
#include "PlayerController_Base.generated.h"

class UMyHUDWidget;
/**
 * 
 */
UCLASS()
class GAMJAM25_API APlayerController_Base : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	//HUD RELATED
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

	UPROPERTY(EditDefaultsOnly, Category = PlayerHUD)
	TSubclassOf<UMyHUDWidget> HUDClass;

	UPROPERTY()
	TObjectPtr<UMyHUDWidget> ActiveHUD;

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputMappingContext> MappingContext;

	UPROPERTY()
	TObjectPtr<AActor> LocalPlayerCharacter;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UIADataConfig> InputActions;

	void Move(const FInputActionInstance& Instance);
	void Look(const FInputActionInstance& Instance);
	void Action(const FInputActionInstance& Instance);
	void Fire(const FInputActionInstance& Instance);
	void Jump(const FInputActionInstance& Instance);
	void Scroll(const FInputActionInstance& Instance);

private:
	UFUNCTION()
	void UpdateScore(uint8 Score);

	UFUNCTION()
	void UpdateHealth(float NewHealth);

	UFUNCTION()
	void GameWin();
};
