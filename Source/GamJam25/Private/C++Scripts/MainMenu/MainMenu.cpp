// Fill out your copyright notice in the Description page of Project Settings.


#include "C++Scripts/MainMenu/MainMenu.h"

#include "C++Scripts/MainMenu/ButtonWidget.h"

void UMainMenu::NativeConstruct()
{
	Super::NativeConstruct();

	if (PlayButton)
	{
		if (MenuStyle && !PlayButton->MenuStyleData)
			PlayButton->MenuStyleData = MenuStyle;

		PlayButton->Label = NSLOCTEXT("Menu", "PlayButton", "Play");
		PlayButton->OnClickedButton.AddDynamic(this, &UMainMenu::HandlePlay);
	}

	if (QuitButton)
	{
		if (MenuStyle && !QuitButton->MenuStyleData)
			QuitButton->MenuStyleData = MenuStyle;

		QuitButton->Label = NSLOCTEXT("Menu", "QuitButton", "Quit");
		QuitButton->OnClickedButton.AddDynamic(this, &UMainMenu::HandleQuit);
	}
}

void UMainMenu::NativeDestruct()
{
	if (PlayButton)
	{
		PlayButton->OnClickedButton.RemoveAll(this);
	}

	if (QuitButton)
	{
		QuitButton->OnClickedButton.RemoveAll(this);
	}
	
	Super::NativeDestruct();
}
