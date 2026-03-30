// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ToolData.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable) // blueprint type required to access it as variable in eventgrpah
class UE5_FORGOTTEN_NATURE_API UToolData : public UDataAsset
{

	GENERATED_BODY()

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tool")
    FString name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tool")
    float damage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tool")
    float attackSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tool")
    TSubclassOf<AActor> tool;

	
};
