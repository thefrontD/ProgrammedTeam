// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "TaskMoveToBBEntry.generated.h"

/**
 * 
 */
UCLASS()
class PROGRAMMEDTEAM_API UTaskMoveToBBEntry : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UTaskMoveToBBEntry();
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
