// Fill out your copyright notice in the Description page of Project Settings.

#include "TaskInitMobBBAsset.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../Mob.h"
#include "../Logger.h"

UTaskInitMobBBAsset::UTaskInitMobBBAsset() {
	NodeName = TEXT("Init{AttackDelay}");
}

EBTNodeResult::Type UTaskInitMobBBAsset::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Logger::Print("[UTaskInitMobBBAsset] called", 5);

	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn == nullptr)
		return EBTNodeResult::Failed;
	auto ControllingMob = Cast<AMob>(ControllingPawn);

	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(TEXT("AttackDelay"), ControllingMob->GetAttackDelay());

	return EBTNodeResult::Succeeded;
}
