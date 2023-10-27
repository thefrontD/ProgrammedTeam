// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "DecIsNearbyBBEntry.generated.h"

/**
 * 
 */
UCLASS()
class PROGRAMMEDTEAM_API UDecIsNearbyBBEntry : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()
public:
	UDecIsNearbyBBEntry();
protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

};
