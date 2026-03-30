// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include"GameFramework/PlayerController.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PlayerStatsComponent.h"
#include "ItemInteractionComponent.h"

APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	statsComponent = CreateDefaultSubobject<UPlayerStatsComponent>(TEXT("Stats Component"));
	itemInteractionComponent = CreateDefaultSubobject<UItemInteractionComponent>(TEXT("Item Interaction Component"));
	

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* playerController = Cast<APlayerController>(Controller); // stores the player controller that is stored on the player
	if (!playerController) return; // only proceed if the controller of this script is stored here

	ULocalPlayer* localPlayer = playerController->GetLocalPlayer(); // checks when inputs are used
	if (!localPlayer) return;

	UEnhancedInputLocalPlayerSubsystem* subSystem = localPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	if (!subSystem) return;

	subSystem->AddMappingContext(playerMappingContext, 0); // stores the mapping context from editor into the player controller

	
	cameraSpringArm = Cast<USpringArmComponent>(GetComponentByClass(USpringArmComponent::StaticClass()));
	playerCamera = FindComponentByClass<UCameraComponent>();

	if (playerCamera)
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("Camera found!"));

	
	
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

	UEnhancedInputComponent* enhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (!enhancedInput) return;

	if (movementAction)
		enhancedInput->BindAction(movementAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Movement);
	if (lookAction)
		enhancedInput->BindAction(lookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Looking);
	if (interactAction)
		enhancedInput->BindAction(interactAction, ETriggerEvent::Completed, this, &APlayerCharacter::Interacting);
	if (useAction)
		enhancedInput->BindAction(useAction, ETriggerEvent::Completed, this, &APlayerCharacter::Using);
	if (dropAction)
		enhancedInput->BindAction(dropAction, ETriggerEvent::Completed, this, &APlayerCharacter::Dropping);
	if (jumpAction)
		enhancedInput->BindAction(jumpAction, ETriggerEvent::Completed, this, &APlayerCharacter::Jump);
	if (inventoryAction)
		enhancedInput->BindAction(inventoryAction, ETriggerEvent::Completed, this, &APlayerCharacter::Inventory);



}

void APlayerCharacter::Movement(const FInputActionValue& value)
{
	FVector2D movement2D = value.Get<FVector2D>(); // stores the movement values.

	if (!Controller) return;

	UCameraComponent* camera = FindComponentByClass<UCameraComponent>(); // gets the camera in the player blueprint.
	if (!camera) return;


	const FRotator yawRotation(0, Controller->GetControlRotation().Yaw, 0);

	// forward, left, right and backwards are all dependent on the rotation the player is facing
	const FVector forward = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
	const FVector right = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);

	// makes the character move. Takes movement from max walk speed in editor 
	AddMovementInput(forward, movement2D.Y);
	AddMovementInput(right, movement2D.X);

//	AddControllerYawInput(yawRotation);


}



void APlayerCharacter::Looking(const FInputActionValue& value)
{
	FVector2D looking2D = value.Get<FVector2D>();

	if (itemInteractionComponent->inventoryOpen) return; // dont want camera moving when inventory tab is open
	if (!Controller) return;

	if (!cameraSpringArm) return;
	AddControllerYawInput(looking2D.X * 2);
	FRotator cameraRotation = cameraSpringArm->GetRelativeRotation(); // gets rotation of camera.

	cameraRotation.Pitch = FMath::Clamp(FRotator::NormalizeAxis(cameraRotation.Pitch) + (looking2D.Y * 2), -60, 60); 
	cameraRotation.Yaw = 0;
	cameraSpringArm->SetRelativeRotation(cameraRotation); // rotates camears pitch
	
	
}   

void APlayerCharacter::Interacting(const FInputActionValue& value)
{
	itemInteractionComponent->PickItemUp();




}


void APlayerCharacter::Using(const FInputActionValue& value)
{
	GEngine->AddOnScreenDebugMessage(01, 3, FColor::Purple, FString::Printf(TEXT("Using Item")));

}

void APlayerCharacter::Dropping(const FInputActionValue& value)
{
	GEngine->AddOnScreenDebugMessage(01, 3, FColor::Purple, TEXT("Dropping Item"));
}


void APlayerCharacter::Inventory(const FInputActionValue& value)
{
	itemInteractionComponent->ShowInventory();
}

