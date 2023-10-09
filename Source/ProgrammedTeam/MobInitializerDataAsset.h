// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MobInitializerDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class PROGRAMMEDTEAM_API UMobInitializerDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class AWeapon> GunClass;
};
