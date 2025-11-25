// Fill out your copyright notice in the Description page of Project Settings.


#include "C++Scripts/MainMenu/MenuController.h"

#include "Blueprint/UserWidget.h"
#include "C++Scripts/MainMenu/ButtonWidget.h"
#include "C++Scripts/MainMenu/MainMenu.h"
#include "C++Scripts/MainMenu/MenuStyleDA.h"
#include "Kismet/GameplayStatics.h"

#if WITH_EDITOR
#include "Editor/EditorEngine.h"
#include "Editor.h"
#endif

void AMenuController::BeginPlay()
{
	Super::BeginPlay();

	if (MainMenuClass)
	{
		MainMenu = CreateWidget<UMainMenu>(this, MainMenuClass);
		if (MainMenu)
		{
			MainMenu->AddToViewport();
			MainMenu->OnPlayRequest.AddDynamic(this, &AMenuController::HandleOnPlayGame);
			MainMenu->OnQuitRequest.AddDynamic(this, &AMenuController::HandleOnQuitGame);
		}
	}

	FInputModeUIOnly InputMode;

	InputMode.SetWidgetToFocus(MainMenu->PlayButton->TakeWidget());
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	SetInputMode(InputMode);
	bShowMouseCursor = true;
}

void AMenuController::BeginDestroy()
{
	if (MainMenu)
	{
		MainMenu->OnQuitRequest.RemoveAll(this);
	}
	
	Super::BeginDestroy();
}

void AMenuController::HandleOnPlayGame()
{
	FSoftObjectPath MapRef = MenuFlow->GameplayLevel.ToSoftObjectPath();
	if (!MapRef.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("GameplayMap soft path is Invalid"));
		return;
	}

	FString MapPath = MapRef.ToString();
	FName MapName = FName(*FPackageName::ObjectPathToPackageName(MapPath));
	UGameplayStatics::OpenLevel(this, MapName);
}

void AMenuController::HandleOnQuitGame()
{
#if WITH_EDITOR
	if (GEditor)
	{
		if (GEditor->IsPlayingSessionInEditor())
		{
			GEditor->RequestEndPlayMap();
			return;
		}

		UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, false);
	}
#else
	UWorld* World = GetWorld();
	if (IsValid(World))
	{
		UKismetSystemLibrary::QuitGame(World, nullptr, EQuitPreference::Quit, false);
	}
#endif
}
