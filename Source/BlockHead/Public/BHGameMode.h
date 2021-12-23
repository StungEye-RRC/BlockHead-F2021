// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BHGameMode.generated.h"

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

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG")
	TSubclassOf<UUserWidget> DefaultLevelCompleteWidget;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG")
	UUserWidget* LevelCompleteWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG")
	TSubclassOf<UUserWidget> DefaultGameCompleteWidget;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG")
	UUserWidget* GameCompleteWidget;

private:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Levels")
	TArray<FString> Levels;

	APlayerController* Controller;

	int32 CurrentLevelIndex;
	FString NextLevel;

	void CheckLevel();
};
