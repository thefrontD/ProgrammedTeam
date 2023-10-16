// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "TaskAim.generated.h"

/**
 * 
 */
UCLASS()
class PROGRAMMEDTEAM_API UTaskAim : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UTaskAim();

	virtual EBTNodeResult::Type ExecuteTask(
		UBehaviorTreeComponent& OwnerComp, 
		uint8* NodeMemory
	) override;
};
