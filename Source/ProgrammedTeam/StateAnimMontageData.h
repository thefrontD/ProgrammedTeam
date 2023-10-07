// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StateAnimMontageData.generated.h"

/**
 * 
 */
class PROGRAMMEDTEAM_API StateAnimMontageData
{
public:
	StateAnimMontageData();
	~StateAnimMontageData();
};

USTRUCT(Atomic, BlueprintType)
struct FStateAnimMontageData {
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere)
		UAnimMontage* Montage;

	UPROPERTY(EditAnywhere)
		float PlayRate;

	UPROPERTY(EditAnywhere)
		FString Section;
};