// Fill out your copyright notice in the Description page of Project Settings.


#include "TaskPatrol.h"
#include "../Logger.h"
#include "../MarkerController.h"
#include "../PatrolComponent.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"

UTaskPatrol::UTaskPatrol() {
	MarginDistance = 200.0f;
}

EBTNodeResult::Type UTaskPatrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn == nullptr)
		return EBTNodeResult::Failed;
	UPatrolComponent* PatrolComponent = Cast<UPatrolComponent>(ControllingPawn->GetComponentByClass(UPatrolComponent::StaticClass()));
	
	FVector Location;
	if (PatrolComponent->GetDestination(Location)) {

		bool bNearBy = FVector::DistXY(FVector::ZeroVector, ControllingPawn->GetActorLocation() - Location) < MarginDistance;
		bool bInBattle = OwnerComp.GetBlackboardComponent()->GetValueAsBool(TEXT("bInBattle"));
		if (bNearBy && !bInBattle) {
			PatrolComponent->SetIndexToNext();
		}

		UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
		if (NavSystem == nullptr)
			return EBTNodeResult::Failed;

		UAIBlueprintHelperLibrary::SimpleMoveToLocation(ControllingPawn->Controller, Location);

		return EBTNodeResult::Succeeded;
	}
	else {
		return EBTNodeResult::Failed;
	}
		




	return EBTNodeResult::Type();
}
