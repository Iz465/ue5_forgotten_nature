// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemInteractionComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacter.h"
#include "GameFramework/Character.h"
#include "Tools.h"


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
	/*

	inventoryWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), inventoryWidgetClass);
	inventoryWidgetInstance->AddToViewport();
	inventoryWidgetInstance->SetVisibility(ESlateVisibility::Hidden);
	*/


	player = UGameplayStatics::GetPlayerCharacter(this, 0);
	
}
//deathWidget = CreateWidget<UUserWidget>(GetWorld(), deathWidgetClass);

// Called every frame
void UItemInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


}

void UItemInteractionComponent::PickItemUp()
{

	if(!player) return;

	APlayerCharacter* playerCharacter = Cast<APlayerCharacter>(player);
	if (!playerCharacter) return;

	if (!playerCharacter->playerCamera) return;

	FVector cameraLocation = playerCharacter->playerCamera->GetComponentLocation();

	FVector endLocation = (playerCharacter->playerCamera->GetForwardVector() * grabDistance) + cameraLocation;
	FHitResult hitResult;

	if (GetWorld()->LineTraceSingleByChannel(hitResult, cameraLocation, endLocation, ECC_GameTraceChannel3))
	{
		
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Purple, TEXT("hit an item!"));
		DrawDebugLine(GetWorld(), cameraLocation, endLocation, FColor::Green, true);
		
		ATools* tool = Cast<ATools>(hitResult.GetActor());

		if (tool) GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Purple, TEXT("item is tool!"));

		else GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Purple, TEXT("not child of tool class!"));

	}

	else DrawDebugLine(GetWorld(), cameraLocation, endLocation, FColor::Red, true);


//	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Purple, FString::Printf(TEXT("Camera Location: %s"), *cameraLocation.ToString()));

	
}







void UItemInteractionComponent::ShowInventory()
{
	APawn* pawn = Cast<APawn>(GetOwner());
	if (!pawn) return;
	UCameraComponent* camera = pawn->FindComponentByClass<UCameraComponent>();


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
		if (camera) camera->Activate();
		inventoryOpen = false;
	}



}

