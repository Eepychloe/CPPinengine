// Fill out your copyright notice in the Description page of Project Settings.


#include "C++Scripts/MainMenu/ButtonWidget.h"

#include "C++Scripts/MainMenu/MenuStyleDA.h"
#include "Components/Button.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"

void UButtonWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	if (ButtonText)
	{
		ButtonText->SetText(Label);
		if (MenuStyleData)
		{
			ButtonText->SetFont(MenuStyleData->ButtonFont);
			ButtonText->SetColorAndOpacity(MenuStyleData->TextColor);
		}
	}
	if (WB_Button && MenuStyleData)
	{
		FButtonStyle Style = WB_Button->GetStyle();
		Style.Normal.TintColor = FSlateColor(MenuStyleData->ButtonColor);
		Style.Hovered.TintColor = FSlateColor(MenuStyleData->ButtonHoverColor);
		Style.Pressed.TintColor = FSlateColor(MenuStyleData->ButtonHoverColor);
		WB_Button->SetStyle(Style);
	}
	if (WB_SizeBox)
	{
		WB_SizeBox->SetWidthOverride(MenuStyleData->ButtonSize.X);
		WB_SizeBox->SetHeightOverride(MenuStyleData->ButtonSize.Y);
	}
}

void UButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (WB_Button)
	{
		WB_Button->OnClicked.AddDynamic(this, &UButtonWidget::HandleClicked);
	}
}

void UButtonWidget::HandleClicked()
{
	OnClickedButton.Broadcast();
}
