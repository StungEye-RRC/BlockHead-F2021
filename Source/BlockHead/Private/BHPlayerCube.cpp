// Fill out your copyright notice in the Description page of Project Settings.


#include "BHPlayerCube.h"

#include "BHGameMode.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "BHEndPoint.h"
#include "BHObstacle.h"

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

	GameMode = Cast<ABHGameMode>(GetWorld()->GetAuthGameMode());

	Cube->SetSimulatePhysics(true);
	Mass = Cube->GetMass();

	Cube->OnComponentBeginOverlap.AddDynamic(this, &ABHPlayerCube::OnBeginOverlap);
	Cube->OnComponentHit.AddDynamic(this, &ABHPlayerCube::OnHit);
}

void ABHPlayerCube::OnHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp,
                          FVector NormalImpulse, const FHitResult& Hit) {
	ABHObstacle* Obstacle = Cast<ABHObstacle>(Other);
	if (Obstacle) {
		print("On Hit: Obstacle");
	}
}

void ABHPlayerCube::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                   const FHitResult& SweepResult) {
	ABHEndPoint* EndPoint = Cast<ABHEndPoint>(OtherActor);
	if (EndPoint) {
		print("On Overlap: EndPoint");
	}
}

void ABHPlayerCube::MoveLeftRight(float AxisValue) {
	if (!bLevelEnded) {
		const FVector Impulse(0.0f, AxisValue * SideForce * Mass * FApp::GetDeltaTime(), 0.0f);
		Cube->AddImpulse(Impulse);

	}
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
	PlayerInputComponent->BindAxis("MoveLeftRight", this, &ABHPlayerCube::MoveLeftRight);
}
