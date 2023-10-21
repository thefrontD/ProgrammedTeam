// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "TaskMoveToDestination.generated.h"

/**
 * 
 */
UCLASS()
class PROGRAMMEDTEAM_API UTaskMoveToDestination : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UTaskMoveToDestination();
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	
};
