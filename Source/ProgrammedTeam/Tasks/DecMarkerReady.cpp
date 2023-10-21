// Fill out your copyright notice in the Description page of Project Settings.

#include "DecMarkerReady.h"

UDecMarkerReady::UDecMarkerReady() {
	NodeName = TEXT("MarkerReadyToGo");
}

bool UDecMarkerReady::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	bool InBattle = OwnerComp.GetBlackboardComponent()->GetValueAsBool(TEXT("bInBattle"));

	bool InPosition = OwnerComp.GetBlackboardComponent()->GetValueAsBool(TEXT("bInPosition"));

	return !InBattle && (InPosition);
}
