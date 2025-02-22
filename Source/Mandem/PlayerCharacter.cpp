// Fill out your copyright notice in the Description page of Project Settings.

#include "Mandem/PlayerCharacter.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "CoreGlobals.h"

//Constuctor
APlayerCharacter::APlayerCharacter() 
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//Define Interact function
void APlayerCharacter::InputInteract()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "Interact Button Pressed");
}

//Define Shoot function
void APlayerCharacter::InputShoot()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "Shoot button pressed");
	/*GetWorld()->SpawnActor < (ABullet, GetActorLocation(), GetActorForwardVector());*/
}

//Define Special function
void APlayerCharacter::InputSpecial()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "Special shoot button pressed");
}

//Define Input Function
void APlayerCharacter::InputMove(const FInputActionValue& Value)
{
	//Test Input
	GEngine->AddOnScreenDebugMessage(1, 1.f, FColor::Red, "Input moved");
	
	//Grab and utilize vector
	const FVector2D MovementVector = Value.Get<FVector2D>();
	AddMovementInput(GetActorLocation().XAxisVector, MovementVector.X);
	AddMovementInput(GetActorLocation().YAxisVector, MovementVector.Y);
}

void APlayerCharacter::InputRotate(const FInputActionValue& Value)
{
	FVector2D LookDirection = Value.Get<FVector2D>();

	if (LookDirection.SizeSquared() > 0.05f)
	{
		float TargetDirection = FMath::Atan2(LookDirection.Y, LookDirection.X) * (180.0f / PI);
		FRotator NewDirection = FRotator(0, TargetDirection, 0);
		GetController()->SetControlRotation(NewDirection);
	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Add input mapping context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		//Get local player subsystem
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			//Add input context
			Subsystem->AddMappingContext(InputMapping, 0);
		}
	}

	//Check inputs for character player
	if (UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		Input->BindAction(Interact, ETriggerEvent::Triggered, this, &APlayerCharacter::InputInteract);
		Input->BindAction(Move, ETriggerEvent::Triggered, this, &APlayerCharacter::InputMove);
		Input->BindAction(Shoot, ETriggerEvent::Triggered, this, & APlayerCharacter::InputShoot);
		Input->BindAction(Special, ETriggerEvent::Triggered, this, &APlayerCharacter::InputSpecial);
		Input->BindAction(Rotate, ETriggerEvent::Triggered, this, &APlayerCharacter::InputRotate);
		
	}
}