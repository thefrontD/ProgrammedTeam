// Fill out your copyright notice in the Description page of Project Settings.


#include "ServiceSetMobDestination.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "../Mob.h"
#include "../TeamProgressMarker.h"


UServiceSetMobDestination::UServiceSetMobDestination() {
	NodeName = TEXT("SetDestination");
}

void UServiceSetMobDestination::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn == nullptr) {
		return;
	}
	ATeamProgressMarker* Marker = Cast<ATeamProgressMarker>(ControllingPawn);

	Marker->SetMobDestination();
	
}
