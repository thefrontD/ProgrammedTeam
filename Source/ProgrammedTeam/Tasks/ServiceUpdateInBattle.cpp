// Fill out your copyright notice in the Description page of Project Settings.


#include "ServiceUpdateInBattle.h"
#include "AIController.h"
#include "../TeamProgressMarker.h"
#include "../ProgrammedTeam.h"
#include "BehaviorTree/BlackboardComponent.h"


UServiceUpdateInBattle::UServiceUpdateInBattle() {
	NodeName = TEXT("UpdateReady");
}

void UServiceUpdateInBattle::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn == nullptr) {
		return;
	}

	auto TeamProgressMarker = Cast<ATeamProgressMarker>(ControllingPawn);

	OwnerComp.GetBlackboardComponent()->SetValueAsBool(
		"bInBattle",
		TeamProgressMarker->CheckTeamInBattle());
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(
		"bInPosition",
		TeamProgressMarker->CheckTeamInPosition());
}
