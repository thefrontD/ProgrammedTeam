// Fill out your copyright notice in the Description page of Project Settings.


#include "ServiceFindTarget.h"
#include "AIController.h"
#include "../ProgrammedTeam.h"
#include "../Mob.h"
#include "DrawDebugHelpers.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "../Logger.h"

UServiceFindTarget::UServiceFindTarget() {
	NodeName = TEXT("FindTarget");
	Interval = 1.0f;
	FindRange = 1000.0f;
}

void UServiceFindTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	Logger::Print("[UServiceFindTarget] called",5);

	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn == nullptr) {
		return;
	}
	auto ControllingMob = Cast<AMob>(ControllingPawn);


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
		AMob* Mob = nullptr;
		//Logger::Print(OverlapResults.Num());
		//OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), nullptr);
		for (auto const& OverlapResult : OverlapResults)
		{
			Mob = Cast<AMob>(OverlapResult.GetActor());
			if (Mob != nullptr && Mob->GetTeamNum() != ControllingMob->GetTeamNum()) {
				//Logger::Print( 1000+Mob->GetTeamNum(), 7);
				//Logger::Print(1000+ ControllingMob->GetTeamNum(), 8);
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), Mob);
				ControllingMob->SetInBattle(true);
				//OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("bInBattle"), true);
			}
			else Mob = nullptr;
		}
		if (Mob == nullptr) {
			ControllingMob->SetInBattle(false);
		}
	}

	DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Green, false, 0.5f);

}
