// Fill out your copyright notice in the Description page of Project Settings.


#include "BHPawn.h"
#include "BHGameMode.h"

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
	Cube->OnComponentHit.AddDynamic(this, &ABHPawn::OnHit);
	Cube->OnComponentBeginOverlap.AddDynamic(this, &ABHPawn::OnBeginOverlap);
	GameMode = Cast<ABHGameMode>(GetWorld()->GetAuthGameMode());

	Cube->SetSimulatePhysics(true); // Needed? Didn't we do this in blueprint?
	Mass = Cube->GetMass();
}

// Called every frame
void ABHPawn::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (!bLevelEnded) {
		// Forward Motion
		const FVector Impulse = FVector(Mass * ForwardForce * DeltaTime, 0.0f, 0.0f);
		Cube->AddImpulse(Impulse);

		// Kill Z
		const FVector ActorLocation = GetActorLocation();
		if (ActorLocation.Z < -30) {
			KillPlayer();
		}

	}

	DeltaSeconds = DeltaTime;
}

// Called to bind functionality to input
void ABHPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveLeftRight", this, &ABHPawn::MoveRight);
}

void ABHPawn::OnHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, FVector NormalImpulse,
                    const FHitResult& Hit) {
}

void ABHPawn::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                             int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
}

void ABHPawn::PlayerDied() {
}

void ABHPawn::MoveRight(float AxisValue) {
	if (!bLevelEnded) {
		const FVector Impulse = FVector(0.0f, Mass * SideForce * DeltaSeconds * AxisValue, 0.0f);
		Cube->AddImpulse(Impulse, "", true);
	}
}

void ABHPawn::KillPlayer() {
}
