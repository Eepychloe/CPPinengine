// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "UObject/Interface.h"
#include "IAInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UIAInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GAMJAM25_API IIAInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Action(const FInputActionInstance& Instance);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Fire(const FInputActionInstance& Instance);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void JumpAction(const FInputActionInstance& Instance);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Move(const FInputActionInstance& Instance);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Look(const FInputActionInstance& Instance);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Scroll(const FInputActionInstance& Instance);
};
