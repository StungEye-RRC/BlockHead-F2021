// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BHPawn.generated.h"

UCLASS()
class BLOCKHEAD_API ABHPawn : public APawn {
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABHPawn();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Setup")
	UStaticMeshComponent* Cube;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Setup")
	class USpringArmComponent* SpringArm;
	// The class keyword forward declares so that we don't need to include the header.

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Setup")
	class UCameraComponent* Camera; // The class keyword forward declares so that we don't need to include the header.

	UPROPERTY(EditAnywhere, Category = "Floats")
	float ForwardForce = 2000;

	UPROPERTY(EditAnywhere, Category = "Floats")
	float SideForce = 5;
};
