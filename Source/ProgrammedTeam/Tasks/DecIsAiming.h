// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "DecIsAiming.generated.h"

/**
 * 
 */
UCLASS()
class PROGRAMMEDTEAM_API UDecIsAiming : public UBTDecorator
{
	GENERATED_BODY()
public:
	UDecIsAiming();
protected:
	virtual bool CalculateRawConditionValue(
		UBehaviorTreeComponent& OwnerComp, 
		uint8* NodeMemory
	) const override;

};
