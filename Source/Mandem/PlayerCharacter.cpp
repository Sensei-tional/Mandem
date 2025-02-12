// Fill out your copyright notice in the Description page of Project Settings.


#include "Mandem/PlayerCharacter.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "CoreGlobals.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerCharacter::InputInteract()
{
	//Define Interact function
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "Interact Button Pressed");
	UE_LOG(LogTemp, Warning, TEXT("Interact Button Pressed"));
}

void APlayerCharacter::InputMove(const FInputActionValue& Value)
{
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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

	if (UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		Input->BindAction(Interact, ETriggerEvent::Triggered, this, &APlayerCharacter::InputInteract);
		Input->BindAction(Move, ETriggerEvent::Triggered, this, &APlayerCharacter::InputMove);
	}
}