// Fill out your copyright notice in the Description page of Project Settings.


#include "BHGameMode.h"

#include <string>

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/OutputDeviceNull.h"

#define print(text) if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green,text); 	UE_LOG(LogTemp, Warning, TEXT(text)); }

ABHGameMode::ABHGameMode() {

}

void ABHGameMode::BeginPlay() {
	Super::BeginPlay();

	Controller = GetWorld()->GetFirstPlayerController();
	Controller->bShowMouseCursor = false;
	FInputModeGameOnly InputMode;
	Controller->SetInputMode(InputMode);

	CheckLevel();

	if (DefaultHUD) {
		HUD = CreateWidget<UUserWidget>(GetWorld(), DefaultHUD);
		HUD->AddToViewport();
	}
}

void ABHGameMode::CheckLevel() {
	const FString CurrentLevelName = CleanedLevelString();
	Levels.Find(CurrentLevelName, CurrentLevelIndex);

	if (CurrentLevelIndex < Levels.Num() - 1) {
		NextLevel = Levels[CurrentLevelIndex + 1];
	} else {
		NextLevel = "End";
	}
}

FString ABHGameMode::CleanedLevelString() {
	const FString Prefix = GetWorld()->StreamingLevelsPrefix;
	const FString CurrentLevelName = GetWorld()->GetMapName();
	return CurrentLevelName.RightChop(Prefix.Len());
}

void ABHGameMode::LoadFinalMenu(bool bWonGame) {
	if (DefaultGameCompleteWidget) {
		GameCompleteWidget = CreateWidget<UUserWidget>(GetWorld(), DefaultGameCompleteWidget);

		const FString FunctionCall{bWonGame ? "SetWinOrLoss true" : "SetWinOrLoss false"};

		FOutputDeviceNull Ar;
		GameCompleteWidget->CallFunctionByNameWithArguments(*FunctionCall, Ar, nullptr, true);

		GameCompleteWidget->AddToViewport();
		Controller->bShowMouseCursor = true;
		FInputModeUIOnly InputMode;
		Controller->SetInputMode(InputMode);
	} else {
		UE_LOG(LogTemp, Warning, TEXT("No Default Game Complete Widget Specified in Game Mode."));
	}
}

void ABHGameMode::EndGame() {
	print("GameMode EndGame")
	LoadFinalMenu(false);
}

void ABHGameMode::LevelComplete() {
	print("GameMode LevelComplete")

	if (DefaultLevelCompleteWidget) {
		LevelCompleteWidget = CreateWidget<UUserWidget>(GetWorld(), DefaultLevelCompleteWidget);
		LevelCompleteWidget->AddToViewport();
	} else {
		print("No Default Level Complete Widget has Been Set in the Game Mode.")
	}

	GetWorldTimerManager().SetTimer(LevelSwapTimer, this, &ABHGameMode::LoadNextLevel, 2.0f, false);
}

void ABHGameMode::LoadNextLevel() {

	FName LevelToLoad = FName(*NextLevel);

	if (Levels.Contains(NextLevel)) {
		UGameplayStatics::OpenLevel(this, LevelToLoad, true);
	} else {
		// Show game complete widget!
		if (LevelCompleteWidget) {
			LevelCompleteWidget->RemoveFromParent();
			LoadFinalMenu(true);
		}
	}
}
