// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BHGameMode.generated.h"

// class UUserWidget; // Forward Declaration Not Required.

/**
 * 
 */
UCLASS()
class BLOCKHEAD_API ABHGameMode : public AGameModeBase {
	GENERATED_BODY()

public:
	ABHGameMode();
	void EndGame();
	void LevelComplete();
	void LoadNextLevel();

	FString CleanLevelString();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG")
	TSubclassOf<UUserWidget> DefaultLevelCompleteWidget;
	UUserWidget* LevelCompleteWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG")
	TSubclassOf<UUserWidget> DefaultGameCompleteWidget;
	UUserWidget* GameCompleteWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG")
	TSubclassOf<UUserWidget> DefaultHUD;
	UUserWidget* HUD;

private:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Levels")
	TArray<FString> Levels;

	APlayerController* Controller;

	int32 CurrentLevelIndex = 0;
	FString NextLevel;

	FTimerHandle LevelSwapTimer;

	void CheckLevel();
	void LoadFinalMenu(bool bGameOver);
};
