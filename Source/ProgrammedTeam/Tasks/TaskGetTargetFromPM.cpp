// Fill out your copyright notice in the Description page of Project Settings.

#include "TaskGetTargetFromPM.h"
#include "../Mob.h"

UTaskGetTargetFromPM::UTaskGetTargetFromPM() {
	NodeName = TEXT("GetTargetFromPM");
}

EBTNodeResult::Type UTaskGetTargetFromPM::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn == nullptr)
		return EBTNodeResult::Failed;
	auto ControllingMob = Cast<AMob>(ControllingPawn);

	AMob* Target = ControllingMob->GetTargetFromPM();
	OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), Target);
	ControllingMob->SetTarget(Target);
	return EBTNodeResult::Succeeded;
}
