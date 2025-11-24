// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HealthInterface.generated.h"

class FOnHealthChanged;
// This class does not need to be modified.
UINTERFACE()
class UHealthInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GAMJAM25_API IHealthInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual float GetMaxHealth() const = 0;
	virtual FOnHealthChanged& GetHealthChangedDelegate() = 0;
};
