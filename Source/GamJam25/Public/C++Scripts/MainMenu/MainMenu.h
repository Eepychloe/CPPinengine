// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

/**
 * 
 */

class UButtonWidget;
class UMenuStyleDA;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlay);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnQuit);

UCLASS()
class GAMJAM25_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = Events)
	FOnPlay OnPlayRequest;

	UPROPERTY(BlueprintAssignable, Category = Events)
	FOnQuit OnQuitRequest;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Style)
	TObjectPtr<UMenuStyleDA> MenuStyle;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButtonWidget> PlayButton;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButtonWidget> QuitButton;

protected:

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UFUNCTION()
	void HandlePlay(){OnPlayRequest.Broadcast();}

	UFUNCTION()
	void HandleQuit(){OnQuitRequest.Broadcast();}
};
