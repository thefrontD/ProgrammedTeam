// Fill out your copyright notice in the Description page of Project Settings.

#include "TaskMoveToDestination.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "AIController.h"
#include "../Mob.h"
#include "../MobController.h"

UTaskMoveToDestination::UTaskMoveToDestination() {
	NodeName = "MoveToDestination";
}

EBTNodeResult::Type UTaskMoveToDestination::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn == nullptr)
		return EBTNodeResult::Failed;
	
	auto ControllingMob = Cast<AMob>(ControllingPawn);
	if(ControllingMob == nullptr)
		return EBTNodeResult::Failed;

	Logger::Print( "[UTaskMoveToDestination]" + ControllingMob->GetDestination().ToString(), 6);

	UAIBlueprintHelperLibrary::SimpleMoveToLocation(
		ControllingMob->Controller,
		ControllingMob->GetDestination());

	return EBTNodeResult::Succeeded;
}
