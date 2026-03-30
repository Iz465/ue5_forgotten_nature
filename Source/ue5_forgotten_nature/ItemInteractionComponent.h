// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Blueprint/UserWidget.h"
#include "ItemInteractionComponent.generated.h"


class AActor;
class ACharacter;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class UE5_FORGOTTEN_NATURE_API UItemInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UItemInteractionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void PickItemUp();
	void ShowInventory();
	//void DropItem();
	//void SwitchItem();
	//void UseItem();

	UPROPERTY(EditAnywhere)
	AActor* headLocation;

	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<UUserWidget> inventoryWidgetClass;

	UPROPERTY()
	UUserWidget* inventoryWidgetInstance;

	bool inventoryOpen = false;

	ACharacter* player;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float grabDistance = 800;
		
};
