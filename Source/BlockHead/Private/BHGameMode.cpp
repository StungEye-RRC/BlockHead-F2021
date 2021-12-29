// Fill out your copyright notice in the Description page of Project Settings.


#include "BHGameMode.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

ABHGameMode::ABHGameMode() {
}

void ABHGameMode::BeginPlay() {
	Super::BeginPlay();

	Controller = GetWorld()->GetFirstPlayerController();
	FInputModeGameOnly InputMode;
	Controller->SetInputMode(InputMode);
	Controller->bShowMouseCursor = false;

	CheckLevel();

	if (DefaultHUD) {
		// UE_LOG(LogTemp, Warning, TEXT("Attempting to create HUD"));
		HUD = CreateWidget<UUserWidget>(GetWorld(), DefaultHUD);
		HUD->AddToViewport();
	}

}

void ABHGameMode::CheckLevel() {
	const FString CurrentLevelName = GetWorld()->GetMapName();
	Levels.Find(CurrentLevelName, CurrentLevelIndex);

	if (CurrentLevelIndex < Levels.Num() - 1) {
		NextLevel = Levels[CurrentLevelIndex + 1];
	} else {
		NextLevel = "End";
	}
}

void ABHGameMode::EndGame() {
	const FString LevelString = GetWorld()->GetMapName();
	const FName LevelToLoad = FName(*LevelString);
	UGameplayStatics::OpenLevel(this, LevelToLoad, true);
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
			if (DefaultGameCompleteWidget) {
				GameCompleteWidget = CreateWidget<UUserWidget>(GetWorld(), DefaultGameCompleteWidget);
				GameCompleteWidget->AddToViewport();

				Controller->bShowMouseCursor = true;
				FInputModeUIOnly InputMode;
				Controller->SetInputMode(InputMode);
			} else {
				UE_LOG(LogTemp, Warning, TEXT("No Default Game Complete Widget Selected!"));
			}
		}
	}
}
