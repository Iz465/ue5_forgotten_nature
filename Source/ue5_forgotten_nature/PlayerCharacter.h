// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h" // needed for getting the values of an input
#include "PlayerStatsComponent.h"
#include "ItemInteractionComponent.h"
#include "PlayerCharacter.generated.h"

class UInputMappingContext; // forward declared as only stores pointer
class UInputAction; // forward declared as only stores pointer
class UCameraComponent;
class USpringArmComponent;
//class UItemInteractionComponent;
//class UPlayerStatsComponent;

UCLASS()
class UE5_FORGOTTEN_NATURE_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	

protected:
	// Called when the game starts or when spawned

	
	virtual void BeginPlay() override;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* playerMappingContext;
	
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* movementAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* lookAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* interactAction;

	UPROPERTY(EditAnywhere, Category = "input")
	UInputAction* useAction;

	UPROPERTY(EditAnywhere, Category = "input")
	UInputAction* dropAction;

	UPROPERTY(EditAnywhere, Category = "input")
	UInputAction* jumpAction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USpringArmComponent* cameraSpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UPlayerStatsComponent* statsComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UItemInteractionComponent* itemInteractionComponent;
	

private: 
	void Movement(const FInputActionValue& value);
	void Looking(const FInputActionValue& value);
	void Interacting(const FInputActionValue& value);
	void Using(const FInputActionValue& value);
	void Dropping(const FInputActionValue& value);

};
