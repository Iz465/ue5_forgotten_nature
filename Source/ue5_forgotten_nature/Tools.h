// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tools.generated.h"


class UToolData;

UCLASS()
class UE5_FORGOTTEN_NATURE_API ATools : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATools();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tool Info")
	TSubclassOf<UToolData> toolData;

};
