// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "DecAllMobInPosition.generated.h"

/**
 * 
 */
UCLASS()
class PROGRAMMEDTEAM_API UDecAllMobInPosition : public UBTDecorator
{
	GENERATED_BODY()
public:
	UDecAllMobInPosition();
protected:
	virtual bool CalculateRawConditionValue(
		UBehaviorTreeComponent& OwnerComp,
		uint8* NodeMemory
	) const override;
};
