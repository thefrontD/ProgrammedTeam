// Fill out your copyright notice in the Description page of Project Settings.

#include "DecIsInBattle.h"
#include "../ProgrammedTeam.h"
#include "BehaviorTree/BlackboardComponent.h"

UDecIsInBattle::UDecIsInBattle() {
    NodeName = TEXT("IsInBattle");
}

bool UDecIsInBattle::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

    bool InBattle = OwnerComp.GetBlackboardComponent()->GetValueAsBool(TEXT("bInBattle"));

    bool InPosition = OwnerComp.GetBlackboardComponent()->GetValueAsBool(TEXT("bInPosition"));

    return InBattle || (!InPosition);
}
