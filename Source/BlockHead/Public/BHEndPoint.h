// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BHEndPoint.generated.h"

UCLASS()
class BLOCKHEAD_API ABHEndPoint : public AActor {
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABHEndPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Configure")
	class UBoxComponent* Box; // Forward declard component class for pointer.
};
