// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "ServiceUpdateInBattle.generated.h"

/**
 * 
 */
UCLASS()
class PROGRAMMEDTEAM_API UServiceUpdateInBattle : public UBTService
{
	GENERATED_BODY()
public:
	UServiceUpdateInBattle();
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
