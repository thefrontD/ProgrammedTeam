// Fill out your copyright notice in the Description page of Project Settings.


#include "ServiceFindTarget.h"
#include "AIController.h"
#include "../ProgrammedTeam.h"
#include "../Mob.h"
#include "DrawDebugHelpers.h"
#include "BehaviorTree/BlackboardComponent.h"

UServiceFindTarget::UServiceFindTarget() {
	NodeName = TEXT("FindTarget");
	Interval = 1.0f;
	FindRange = 1000.0f;
}

void UServiceFindTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);


	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn == nullptr) {
		return;
	}


	auto World = ControllingPawn->GetWorld();
	FVector Center = ControllingPawn->GetActorLocation();
	float DetectRadius = FindRange;


	if (World == nullptr) {
		return;
	}


	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, ControllingPawn);
	bool bResult = World->OverlapMultiByChannel(
		OverlapResults,
		Center,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel1,
		FCollisionShape::MakeSphere(DetectRadius),
		CollisionQueryParam
	);

	if (bResult) {
		for (auto const& OverlapResult : OverlapResults)
		{
			AMob* Mob = Cast<AMob>(OverlapResult.GetActor());

			if (Mob && !(Mob->ActorHasTag(TEXT("Player")))) {
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), Mob);
			}
		}
	}

	DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Green, false, 0.5f);

}
