// Fill out your copyright notice in the Description page of Project Settings.


#include "ServiceSetBBDestination.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "../Mob.h"

UServiceSetBBDestination::UServiceSetBBDestination() {
	NodeName = TEXT("SetBBDestination");
	Interval = 0.2f;
}



void UServiceSetBBDestination::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn == nullptr) {
		return;
	}
	AMob* Mob = Cast<AMob>(ControllingPawn);


	OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("Destination"), Mob->GetDestination());

}
