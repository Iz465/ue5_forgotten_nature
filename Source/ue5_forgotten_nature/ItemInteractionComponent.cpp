// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemInteractionComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values for this component's properties
UItemInteractionComponent::UItemInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UItemInteractionComponent::BeginPlay()
{
	Super::BeginPlay();


	inventoryWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), inventoryWidgetClass);
	inventoryWidgetInstance->AddToViewport();
	inventoryWidgetInstance->SetVisibility(ESlateVisibility::Hidden);

	
}
//deathWidget = CreateWidget<UUserWidget>(GetWorld(), deathWidgetClass);

// Called every frame
void UItemInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

//	GEngine->AddOnScreenDebugMessage(01, 3, FColor::Purple, TEXT("Scanning Item"));


	UCameraComponent* camera = GetOwner()->FindComponentByClass<UCameraComponent>();

	if (!camera) return;

	FVector startLocation = GetOwner()->GetActorLocation();
	FVector endLocation = startLocation + (camera->GetForwardVector() * 400);

	FHitResult hitResult;
	FVector boxSize = FVector(30, 30, 30);
	FCollisionShape boxShape = FCollisionShape::MakeBox(boxSize);

	bool canPickUP = GetWorld()->SweepSingleByChannel(hitResult, startLocation, endLocation, FQuat::Identity, ECC_Visibility, boxShape);
	DrawDebugLine(GetWorld(), startLocation, endLocation, FColor::Green, false, 0.1f);


	if (canPickUP)
	{
	//	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Emerald, TEXT("Item can be picked up"));
	}
}

void UItemInteractionComponent::PickItemUp()
{

	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Purple, TEXT("Item Picked Up"));
}

void UItemInteractionComponent::ShowInventory()
{
	APawn* pawn = Cast<APawn>(GetOwner());
	if (!pawn) return;

	APlayerController* controller = Cast<APlayerController>(pawn->GetController());
	if (!controller) return;

	if (!inventoryOpen)
	{
		inventoryWidgetInstance->SetVisibility(ESlateVisibility::Visible);
	
		controller->SetIgnoreMoveInput(true);
		controller->SetIgnoreLookInput(true);
		
		inventoryOpen = true;
	}

	else
	{
		inventoryWidgetInstance->SetVisibility(ESlateVisibility::Hidden);
		controller->SetIgnoreMoveInput(false);
		controller->SetIgnoreLookInput(false);

		inventoryOpen = false;
	}



}

