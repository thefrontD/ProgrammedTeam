// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "ServiceSetMobDestination.generated.h"

/**
 * 
 */
UCLASS()
class PROGRAMMEDTEAM_API UServiceSetMobDestination : public UBTService
{
	GENERATED_BODY()
public:
	UServiceSetMobDestination();
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
