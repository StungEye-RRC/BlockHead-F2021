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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	int killZThreshold = -30;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	bool bHardStopOnCrash = false;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float ForwardForce = 2000;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float SideForce = 5;

	class ABHGameMode* GameMode;
	bool bLevelEnded = false;
	float Mass;
	float DeltaSeconds;

	FTimerHandle EndGameTimer;

	UFUNCTION()
	void OnHit(class UPrimitiveComponent* MyComp, AActor* Other,
	           class UPrimitiveComponent* OtherComp,
	           FVector NormalImpulse,
	           const FHitResult& Hit);

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp,
	                    AActor* OtherActor,
	                    UPrimitiveComponent* OtherComp,
	                    int32 OtherBodyIndex,
	                    bool bFromSweep,
	                    const FHitResult& SweepResult);

	void PlayerDied();
	void MoveRight(float AxisValue);
	void KillPlayer();
};
