// Fill out your copyright notice in the Description page of Project Settings.

#include "TaskInitMobBBAsset.h"
//#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../Logger.h"

UTaskInitMobBBAsset::UTaskInitMobBBAsset() {
	NodeName = TEXT("Init{Target, bInBattle, Destination}");
}

EBTNodeResult::Type UTaskInitMobBBAsset::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Logger::Print("[UTaskInitMobBBAsset] called", 5);

	OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), nullptr);
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("bInBattle"), false);
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("Destination"), FVector::ZeroVector);


	return EBTNodeResult::Succeeded;
}
