// Fill out your copyright notice in the Description page of Project Settings.


#include "BHPlayerCube.h"
#define print(text) if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green,text); 	UE_LOG(LogTemp, Warning, TEXT("text")); }

// Sets default values
ABHPlayerCube::ABHPlayerCube() {
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	print("Constructor");
}

// Called when the game starts or when spawned
void ABHPlayerCube::BeginPlay() {
	Super::BeginPlay();
	print("BeginPlayer");
}

// Called every frame
void ABHPlayerCube::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	// print("Tick");
}

// Called to bind functionality to input
void ABHPlayerCube::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
