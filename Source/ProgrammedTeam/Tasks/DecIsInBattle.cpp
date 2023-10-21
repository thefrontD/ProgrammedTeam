// Fill out your copyright notice in the Description page of Project Settings.

#include "DecIsInBattle.h"
#include "../ProgrammedTeam.h"
#include "../Mob.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UDecIsInBattle::UDecIsInBattle() {
    NodeName = TEXT("IsInBattle");
}

bool UDecIsInBattle::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

    auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
    if (ControllingPawn == nullptr) {
        return false;
    }

    auto ControllingMob = Cast<AMob>(ControllingPawn);

    bool InBattle = ControllingMob->IsInBattle();

    return InBattle;
}
