// Fill out your copyright notice in the Description page of Project Settings.


#include "TaskAim.h"
#include "AIController.h"
#include "../Mob.h"
UTaskAim::UTaskAim() {
	NodeName = (TEXT("Aim"));
}

EBTNodeResult::Type UTaskAim::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	auto Mob = Cast<AMob>(OwnerComp.GetAIOwner()->GetPawn());
	Mob->BeginActionC();

	return EBTNodeResult::Succeeded;
}
