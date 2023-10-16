// Fill out your copyright notice in the Description page of Project Settings.


#include "TaskAttack.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../Mob.h"

UTaskAttack::UTaskAttack() {
	NodeName = TEXT("AttackTarget");
}

EBTNodeResult::Type UTaskAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto ControllingPawn = Cast<AMob>(OwnerComp.GetAIOwner()->GetPawn());
	
	//OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), Mob);
	ControllingPawn->SetTarget(
		Cast<AMob>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("Target")))
	);
	ControllingPawn->BeginActionA();

	return EBTNodeResult::Type();
}
