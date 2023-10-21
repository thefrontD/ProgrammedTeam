// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "TaskPatrolNextIndex.generated.h"

/**
 * 
 */
UCLASS()
class PROGRAMMEDTEAM_API UTaskPatrolNextIndex : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UTaskPatrolNextIndex();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UPROPERTY(VisibleAnywhere)
		float MarginDistance;
};
