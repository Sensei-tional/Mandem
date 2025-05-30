// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "PlayerCharacter.generated.h"


UCLASS()
class MANDEM_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputMappingContext* InputMapping;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputAction* Interact;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputAction* Reload;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputAction* Shoot;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputAction* Move;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputAction* Rotate;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputAction* Special;

	void InputInteract();
	void InputSpecial();
	void InputShoot();
	void InputReload();
	void InputMove(const FInputActionValue& Value);
	void InputRotate(const FInputActionValue& Value);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
