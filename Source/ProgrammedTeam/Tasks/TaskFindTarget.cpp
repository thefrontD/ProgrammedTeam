// Fill out your copyright notice in the Description page of Project Settings.

#include "TaskFindTarget.h"
#include "AIController.h"
#include "../ProgrammedTeam.h"
#include "../TeamProgressMarker.h"
#include "../Mob.h"
#include "DrawDebugHelpers.h"
#include "BehaviorTree/BlackboardComponent.h"

UTaskFindTarget::UTaskFindTarget() {
	NodeName = TEXT("FindTarget");
	FindRange = 2500.f;
}

EBTNodeResult::Type UTaskFindTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	//Mob을 받아온다
	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn == nullptr) {
		return EBTNodeResult::Failed;
	}
	//World에 콜라이더를 만들거라서 World 도 받아온다
	auto World = ControllingPawn->GetWorld();
	if (World == nullptr) {
		return EBTNodeResult::Failed;
	}

	//Location을 받아와서 중심으로 삼아 CollisionQueryParam 을 만든다.
	FVector Center = ControllingPawn->GetActorLocation();
	float DetectRadius = FindRange;

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


	//auto ControllingMob = Cast<AMob>(ControllingPawn);
	auto ControllingPM = Cast<ATeamProgressMarker>(ControllingPawn);
	bool NewbInBattle = false;
	//거의 항상 Result 는 true이다. 바닥등 다른 오브젝트도 감지하기 때문에
	if (bResult) {
		AMob* Mob;
		ControllingPM->Enemies.Empty();
		for (auto OverlapResult : OverlapResults)
		{
			Mob = Cast<AMob>(OverlapResult.GetActor());
			if (Mob == nullptr)
				continue;
			if (Mob->GetTeamNum() == 0) {
				Mob = nullptr;
				continue;
			}

			//OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), Mob);
			NewbInBattle = true;
			//OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("bInBattle"), true);
			//ControllingMob->SetInBattle(true);
			ControllingPM->Enemies.AddUnique(Mob);
			/*ControllingMob->SetTarget(
				Cast<AMob>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("Target")))
			);*/

			//OwnerComp.GetAIOwner()->StopMovement();

			//return EBTNodeResult::Succeeded; //적은 하나면 충분하다
		}

		//if(ControllingPM->Enemies.Num() == 0)
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("bInBattle"), NewbInBattle);
		//ControllingMob->SetInBattle(false);
		//ControllingMob->SetTarget(nullptr);
		
	}

	DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Green, false, 0.5f);


	return EBTNodeResult::Succeeded;
}
