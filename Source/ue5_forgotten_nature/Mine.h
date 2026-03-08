// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Mine.generated.h"

class UPrimitiveComponent;
class UStaticMeshComponent;

UCLASS()
class UE5_FORGOTTEN_NATURE_API AMine : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMine();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* mineMesh;

	UPROPERTY(EditAnywhere, Category = "Stats")
	float damage = 10;
	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* overlappedComp, AActor* otherActor,
		UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep,
		const FHitResult& sweepResult);
	
};
