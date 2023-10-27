// Fill out your copyright notice in the Description page of Project Settings.

#include "DecIsNearbyBBEntry.h"
#include "AIController.h"
#include "../Mob.h"
#include "BehaviorTree/BTDecorator.h"
#include "BehaviorTree/BlackboardComponent.h"

UDecIsNearbyBBEntry::UDecIsNearbyBBEntry() {
	NodeName = "IsNearbyBBEntry";
}

bool UDecIsNearbyBBEntry::CalculateRawConditionValue(
	UBehaviorTreeComponent& OwnerComp, 
	uint8* NodeMemory) const
{

	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn == nullptr)
		return false;
	auto ControllingMob = Cast<AMob>(ControllingPawn);

	//GetBlackboard Actor
	UObject* TargetBBEntryObject = OwnerComp.GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey());
	if (TargetBBEntryObject == nullptr)
		return false;
	AActor* TargetBBEntryActor = Cast<AActor>(TargetBBEntryObject);
	if (TargetBBEntryActor == nullptr)
		return false;
	float Range = ControllingMob->GetRange();

	float dist = FVector::Dist2D(ControllingPawn->GetActorLocation(), TargetBBEntryActor->GetActorLocation());
	if (dist < Range)
		return true;


	return false;
}
