// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStatsComponent.h"

// Sets default values for this component's properties
UPlayerStatsComponent::UPlayerStatsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UPlayerStatsComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPlayerStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPlayerStatsComponent::ApplyDamage(float damage)
{
	health -= damage;
	UE_LOG(LogTemp, Warning, TEXT("Health left: %f"), health);

	if (health <= 0)
		Death.Broadcast();
}

/*
void UPlayerStatsComponent::Death()
{
//	UE_LOG(LogTemp, Warning, TEXT("YOU ARE DEAD"));
//	GetOwner()->Destroy();  // destroys parent, thus destroying all
}
*/

