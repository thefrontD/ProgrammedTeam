// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "ServiceSetBBDestination.generated.h"

/**
 * Not Using
 * 무슨이유에서인지 제대로 작동하지 않아 다른 함수로 대체함
 */
UCLASS()
class PROGRAMMEDTEAM_API UServiceSetBBDestination : public UBTService
{
	GENERATED_BODY()
public:
	UServiceSetBBDestination();
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
