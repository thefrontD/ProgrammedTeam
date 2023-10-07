// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "StateAnimMontageData.h"
#include "AnimMontageDataAsset.generated.h"


/**
 * 
 */
UCLASS()
class PROGRAMMEDTEAM_API UAnimMontageDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	TArray<FStateAnimMontageData> AnimMontageDataArray;

};
