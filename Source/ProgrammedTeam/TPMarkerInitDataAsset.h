// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TPMarkerInitDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class PROGRAMMEDTEAM_API UTPMarkerInitDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		USkeletalMesh* Mesh;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AMob> SpawnClass;

	UPROPERTY(EditAnywhere)
		TArray<FVector> OffsetList;
};
