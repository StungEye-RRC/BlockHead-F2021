// Fill out your copyright notice in the Description page of Project Settings.


#include "BHPlayerCube.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

#define print(text) if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green,text); 	UE_LOG(LogTemp, Warning, TEXT(text)); }

// Sets default values
ABHPlayerCube::ABHPlayerCube() {
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	print("Constructor");

	Cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(Cube);

	/* These are being set from Blueprint but could be set here.
	  
		SpringArm->SetRelativeRotation(FRotator(-20, 0, 0));
		SpringArm->TargetArmLength = 500;
		SpringArm->bInheritPitch = false;
		SpringArm->bInheritYaw = false;
		SpringArm->bInheritRoll = false;
		SpringArm->bEnableCameraLag = true;
	*/

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	RootComponent = Cube;

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void ABHPlayerCube::BeginPlay() {
	Super::BeginPlay();
	print("BeginPlayer");

	Cube->SetSimulatePhysics(true);
	Mass = Cube->GetMass();

}

// Called every frame
void ABHPlayerCube::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (!bLevelEnded) {
		const FVector Impulse(ForwardForce * Mass * DeltaTime, 0.0f, 0.0f);
		Cube->AddImpulse(Impulse);
	}

}

// Called to bind functionality to input
void ABHPlayerCube::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
