// Fill out your copyright notice in the Description page of Project Settings.


#include "ServiceSetBBDestination.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "../Mob.h"
#include "../Logger.h"

UServiceSetBBDestination::UServiceSetBBDestination() {
	NodeName = TEXT("SetBBDestination");
	Interval = 0.2f;
}



void UServiceSetBBDestination::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	//Logger::Print("[UServiceSetBBDestination] called",4);

	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn == nullptr) {
		return;
	}
	AMob* Mob = Cast<AMob>(ControllingPawn);

	Logger::Print("[UServiceSetBBDestination]" + Mob->GetDestination().ToString(), 4);
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("Destination"), Mob->GetDestination());

}
