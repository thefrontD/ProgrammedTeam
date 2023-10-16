// Fill out your copyright notice in the Description page of Project Settings.


#include "DecIsAiming.h"
#include "AIController.h"
#include "../Mob.h"

UDecIsAiming::UDecIsAiming() {

	NodeName = TEXT("IsAiming");
}

bool UDecIsAiming::CalculateRawConditionValue(
	UBehaviorTreeComponent& OwnerComp, 
	uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	auto Pawn = OwnerComp.GetAIOwner()->GetPawn();
	if (Pawn == nullptr)
		return false;

	auto Mob = Cast<AMob>(OwnerComp.GetAIOwner()->GetPawn());
	if (Mob == nullptr)
		return false;

	return Mob->GetAiming();
}
