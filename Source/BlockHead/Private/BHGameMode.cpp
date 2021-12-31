// Fill out your copyright notice in the Description page of Project Settings.


#include "BHGameMode.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/OutputDeviceNull.h"

ABHGameMode::ABHGameMode() {
}

void ABHGameMode::BeginPlay() {
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Begin Play"));
	Controller = GetWorld()->GetFirstPlayerController();
	FInputModeGameOnly InputMode;
	Controller->SetInputMode(InputMode);
	Controller->bShowMouseCursor = false;

	CheckLevel();

	if (DefaultHUD) {
		HUD = CreateWidget<UUserWidget>(GetWorld(), DefaultHUD);
		HUD->AddToViewport();
	}

}

void ABHGameMode::CheckLevel() {
	const FString CurrentLevelName = CleanLevelString();

	Levels.Find(CurrentLevelName, CurrentLevelIndex);

	if (CurrentLevelIndex < Levels.Num() - 1) {
		NextLevel = Levels[CurrentLevelIndex + 1];
	} else {
		NextLevel = "End";
	}
}

void ABHGameMode::LoadFinalMenu(bool bWonGame) {
	if (DefaultGameCompleteWidget) {
		FOutputDeviceNull Ar;
		const FString WinOrLossText{bWonGame ? "setWinOrLoss true" : "setWinOrLoss false"};

		GameCompleteWidget = CreateWidget<UUserWidget>(GetWorld(), DefaultGameCompleteWidget);
		GameCompleteWidget->CallFunctionByNameWithArguments(*WinOrLossText, Ar, nullptr, true);
		GameCompleteWidget->AddToViewport();

		const FInputModeUIOnly InputMode;
		Controller->SetInputMode(InputMode);
		Controller->bShowMouseCursor = true;
	} else {
		UE_LOG(LogTemp, Warning, TEXT("No Default Game Complete Widget Selected!"));
	}
}

void ABHGameMode::EndGame() {
	// Reload the game current level commented out. 
	/*
	const FString LevelString = CleanLevelString();
	const FName LevelToLoad = FName(*LevelString);
	UGameplayStatics::OpenLevel(this, LevelToLoad, true);
	*/
	LoadFinalMenu(false);
}

void ABHGameMode::LevelComplete() {
	if (DefaultLevelCompleteWidget) {
		LevelCompleteWidget = CreateWidget<UUserWidget>(GetWorld(), DefaultLevelCompleteWidget);
		LevelCompleteWidget->AddToViewport();
	} else {
		UE_LOG(LogTemp, Warning, TEXT("No Default Level Complete Widget Selected!"));
	}

	// Wait two seconds before loading the next level after showing the level compete widget.
	GetWorldTimerManager().SetTimer(LevelSwapTimer, this, &ABHGameMode::LoadNextLevel, 2.0f, false);
}

void ABHGameMode::LoadNextLevel() {
	if (Levels.Contains(NextLevel)) {
		FName LevelToLoad = FName(*NextLevel);
		UGameplayStatics::OpenLevel(this, LevelToLoad, true);
	} else {
		if (LevelCompleteWidget) {
			LevelCompleteWidget->RemoveFromParent();
			LoadFinalMenu(true);
		}
	}
}

FString ABHGameMode::CleanLevelString() {
	if (GEngine) {
		FString Prefix = GEngine->GetWorldFromContextObject(GetWorld())->StreamingLevelsPrefix;
		FString LevelName = GetWorld()->GetMapName();
		return LevelName.RightChop(Prefix.Len());
	}

	UE_LOG(LogTemp, Warning, TEXT("ABHGameMode::CleanLevelString cannot find level prefix. GEgine missing."));
	return "ERROR: See log.";
}
