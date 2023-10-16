// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "ServiceFindTarget.generated.h"

/**
 * 
 */
UCLASS()
class PROGRAMMEDTEAM_API UServiceFindTarget : public UBTService
{
	GENERATED_BODY()
public:
	UServiceFindTarget();
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
private:
	float FindRange;
};
