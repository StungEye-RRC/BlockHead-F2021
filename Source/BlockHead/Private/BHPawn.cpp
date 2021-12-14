// Fill out your copyright notice in the Description page of Project Settings.


#include "BHPawn.h"

#include "Engine/StaticMeshSocket.h"

// Sets default values
ABHPawn::ABHPawn() {
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));
	RootComponent = Cube;

}

// Called when the game starts or when spawned
void ABHPawn::BeginPlay() {
	Super::BeginPlay();

}

// Called every frame
void ABHPawn::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABHPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
