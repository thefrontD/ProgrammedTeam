// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DataAssets/Structs/StateAnimMontageData.h"
#include "AnimMontageGettableInterface.generated.h"

UINTERFACE(MinimalAPI)
class UAnimMontageGettableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROGRAMMEDTEAM_API IAnimMontageGettableInterface
{
	GENERATED_BODY()

public:
	virtual FStateAnimMontageData GetAnimMontage(int index) PURE_VIRTUAL(IAnimMontageGettableInterface::GetAnimMontage, return FStateAnimMontageData();)
};
