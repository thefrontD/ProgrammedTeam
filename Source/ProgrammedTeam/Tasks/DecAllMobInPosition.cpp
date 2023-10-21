// Fill out your copyright notice in the Description page of Project Settings.

#include "DecAllMobInPosition.h"

UDecAllMobInPosition::UDecAllMobInPosition() {
	NodeName = TEXT("IsInPosition");
}

bool UDecAllMobInPosition::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	return false;
}

