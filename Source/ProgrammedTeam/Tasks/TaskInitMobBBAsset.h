// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "TaskInitMobBBAsset.generated.h"

/**
 * 
 */
UCLASS()
class PROGRAMMEDTEAM_API UTaskInitMobBBAsset : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UTaskInitMobBBAsset();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
