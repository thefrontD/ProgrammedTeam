// Fill out your copyright notice in the Description page of Project Settings.

#include "TaskMoveToBBEntry.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

UTaskMoveToBBEntry::UTaskMoveToBBEntry() {
	NodeName = TEXT("MoveToBBEntryObject");
}

EBTNodeResult::Type UTaskMoveToBBEntry::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn == nullptr)
		return EBTNodeResult::Failed;

	UObject* Object = OwnerComp.GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey());
	if(Object == nullptr)
		return EBTNodeResult::Failed;
	AActor* Actor = Cast<AActor>(Object);
	if(Actor == nullptr)
		return EBTNodeResult::Failed;

	FVector Location = Actor->GetActorLocation();
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(ControllingPawn->Controller, Location);


	return EBTNodeResult::Type();
}
