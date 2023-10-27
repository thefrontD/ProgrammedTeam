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

	//Mob�� �޾ƿ´�
	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn == nullptr) {
		return EBTNodeResult::Failed;
	}
	//World�� �ݶ��̴��� ����Ŷ� World �� �޾ƿ´�
	auto World = ControllingPawn->GetWorld();
	if (World == nullptr) {
		return EBTNodeResult::Failed;
	}

	//Location�� �޾ƿͼ� �߽����� ��� CollisionQueryParam �� �����.
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
	//���� �׻� Result �� true�̴�. �ٴڵ� �ٸ� ������Ʈ�� �����ϱ� ������
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

			//return EBTNodeResult::Succeeded; //���� �ϳ��� ����ϴ�
		}

		//if(ControllingPM->Enemies.Num() == 0)
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("bInBattle"), NewbInBattle);
		//ControllingMob->SetInBattle(false);
		//ControllingMob->SetTarget(nullptr);
		
	}

	DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Green, false, 0.5f);


	return EBTNodeResult::Succeeded;
}
