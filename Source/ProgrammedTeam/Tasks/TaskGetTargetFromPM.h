// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "TaskGetTargetFromPM.generated.h"

/**
 * 
 */
UCLASS()
class PROGRAMMEDTEAM_API UTaskGetTargetFromPM : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UTaskGetTargetFromPM();
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	
};
