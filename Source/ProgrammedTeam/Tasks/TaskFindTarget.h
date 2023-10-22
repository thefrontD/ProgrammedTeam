// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "TaskFindTarget.generated.h"

/**
 * 
 */
UCLASS()
class PROGRAMMEDTEAM_API UTaskFindTarget : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UTaskFindTarget();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
private:
	float FindRange;
};
