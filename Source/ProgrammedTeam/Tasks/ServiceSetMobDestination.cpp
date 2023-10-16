// Fill out your copyright notice in the Description page of Project Settings.


#include "ServiceSetMobDestination.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "../Mob.h"


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
	AMob* Mob = Cast<AMob>(ControllingPawn);


	OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("Destination"), Mob);

}
