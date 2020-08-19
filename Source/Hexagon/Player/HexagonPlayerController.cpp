// Fill out your copyright notice in the Description page of Project Settings.


#include "HexagonPlayerController.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "Components/CapsuleComponent.h"

#include "Projectile.h"


// Sets default values
AHexagonPlayerController::AHexagonPlayerController()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	FirstPersonCameraComponent = CreateDefaultSubobject< UCameraComponent>(TEXT("Camera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	ShootLocation = CreateDefaultSubobject<USceneComponent>(TEXT("Shoot Location"));
	ShootLocation->SetupAttachment(FirstPersonCameraComponent);
}

// Called when the game starts or when spawned
void AHexagonPlayerController::BeginPlay()
{
	Super::BeginPlay();

	
	
}

void AHexagonPlayerController::MoveForward(float val)
{
	if (val != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), val);
	}
}

void AHexagonPlayerController::MoveRight(float val)
{
	if (val != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), val);
	}
}

void AHexagonPlayerController::Shoot()
{
	UWorld* world = GetWorld();
	if (world == nullptr)return;

	FRotator spawnRotation = GetControlRotation();
	FVector spawnLocation = ShootLocation->GetComponentLocation();

	//Set Spawn Collision Handling Override
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	ActorSpawnParams.Instigator = this;

	AProjectile* p = world->SpawnActor<AProjectile>(ProjectileClass, spawnLocation, spawnRotation, ActorSpawnParams);

	if (p) {
		FVector LaunchDirection = spawnRotation.Vector();
		p->SetUp(LaunchDirection);
	}
}

void AHexagonPlayerController::HitDamage(float amount)
{

}

// Called every frame
void AHexagonPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AHexagonPlayerController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	//Bind shoot events
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &AHexagonPlayerController::Shoot);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &AHexagonPlayerController::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AHexagonPlayerController::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
}

