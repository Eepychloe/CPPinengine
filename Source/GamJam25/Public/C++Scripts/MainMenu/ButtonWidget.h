// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ButtonWidget.generated.h"

class USizeBox;
class UButton;
class UTextBlock;
class UMenuStyleDA;
/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonClicked);

UCLASS()
class GAMJAM25_API UButtonWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable, Category = Events)
	FOnButtonClicked OnClickedButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Style)
	TObjectPtr<UMenuStyleDA> MenuStyleData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Style)
	FText Label = NSLOCTEXT("Menu", "DefaultMenuLabel", "Button");

protected:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> WB_Button;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> ButtonText;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<USizeBox> WB_SizeBox;

	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

	UFUNCTION()
	void HandleClicked();
};
