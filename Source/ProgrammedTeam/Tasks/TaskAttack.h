// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "TaskAttack.generated.h"

/**
 * 
 */
UCLASS()
class PROGRAMMEDTEAM_API UTaskAttack : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UTaskAttack();
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
