// Fill out your copyright notice in the Description page of Project Settings.


#include "BHPawn.h"

#include "Camera/CameraComponent.h"
#include "Engine/StaticMeshSocket.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ABHPawn::ABHPawn() {
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));
	RootComponent = Cube;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(Cube);
	SpringArm->SetRelativeRotation(FRotator(-20, 0, 0));
	SpringArm->TargetArmLength = 400.0f;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritYaw = false;
	SpringArm->bInheritRoll = false;
	SpringArm->bEnableCameraLag = true;
	

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	// The player controller 0 will now auto-posses this pawn.
	AutoPossessPlayer = EAutoReceiveInput::Player0;
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
