// Fill out your copyright notice in the Description page of Project Settings.


#include "Mine.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/HitResult.h"
#include "Components/StaticMeshComponent.h"
#include "PlayerCharacter.h"
#include "PlayerStatsComponent.h"

// Sets default values
AMine::AMine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	mineMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MineMesh")); // creates a static mesh component in the blue print hierarchy named MineMesh
	RootComponent = mineMesh;

}



// Called when the game starts or when spawned
void AMine::BeginPlay()
{
	Super::BeginPlay();

	mineMesh->OnComponentBeginOverlap.AddDynamic(this, &AMine::OnOverlapBegin);
	
}

// Called every frame
void AMine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AMine::OnOverlapBegin(UPrimitiveComponent* overlappedComp, AActor* otherActor,
	UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep,
	const FHitResult& sweepResult)
{
	APlayerCharacter* player = Cast<APlayerCharacter>(otherActor);
	if (!player) return;

	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Purple, TEXT("dharokzz mine"));

	UPlayerStatsComponent* playerStatsComponent = player->FindComponentByClass<UPlayerStatsComponent>();
	
	if (playerStatsComponent) playerStatsComponent->ApplyDamage(damage);

	Destroy();

}




