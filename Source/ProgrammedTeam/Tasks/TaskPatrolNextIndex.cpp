// Fill out your copyright notice in the Description page of Project Settings.

#include "TaskPatrolNextIndex.h"
#include "../PatrolComponent.h"

UTaskPatrolNextIndex::UTaskPatrolNextIndex() {
	MarginDistance = 200.0f;
}

EBTNodeResult::Type UTaskPatrolNextIndex::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn == nullptr)
		return EBTNodeResult::Failed;
	UPatrolComponent* PatrolComponent = Cast<UPatrolComponent>(ControllingPawn->GetComponentByClass(UPatrolComponent::StaticClass()));

	FVector Location;
	if (PatrolComponent->GetDestination(Location)) {

		bool bNearBy = FVector::DistXY(FVector::ZeroVector, ControllingPawn->GetActorLocation() - Location) < MarginDistance;
		if (bNearBy) {
			PatrolComponent->SetIndexToNext();
		}
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
