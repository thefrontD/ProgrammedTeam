// Fill out your copyright notice in the Description page of Project Settings.

#include "TaskFindTarget.h"
#include "AIController.h"
#include "../ProgrammedTeam.h"
#include "../Mob.h"
#include "DrawDebugHelpers.h"
#include "BehaviorTree/BlackboardComponent.h"

UTaskFindTarget::UTaskFindTarget() {
	NodeName = TEXT("FindTarget");
	FindRange = 1000.0f;
}

EBTNodeResult::Type UTaskFindTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	//Mob�� �޾ƿ´�
	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn == nullptr) {
		return EBTNodeResult::Failed;
	}
	auto ControllingMob = Cast<AMob>(ControllingPawn);

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

	//���� �׻� Result �� true�̴�. �ٴڵ� �ٸ� ������Ʈ�� �����ϱ� ������
	if (bResult) {
		AMob* Mob;
		for (auto OverlapResult : OverlapResults)
		{
			Mob = Cast<AMob>(OverlapResult.GetActor());
			if (Mob == nullptr)
				continue;
			if (Mob->GetTeamNum() == ControllingMob->GetTeamNum()) {
				Mob = nullptr;
				continue;
			}

			OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), Mob);
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("bInBattle"), true);
			ControllingMob->SetInBattle(true);
			ControllingMob->SetTarget(
				Cast<AMob>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("Target")))
			);
			OwnerComp.GetAIOwner()->StopMovement();
			//OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("bInBattle"), true);

			return EBTNodeResult::Succeeded; //���� �ϳ��� ����ϴ�
		}

		//������ ���� ������� ������ Ž������ ���� ���� ����
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("bInBattle"), false);
		ControllingMob->SetInBattle(false);
		ControllingMob->SetTarget(nullptr);
	}

	//DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Green, false, 0.5f);


	return EBTNodeResult::Failed;
}
