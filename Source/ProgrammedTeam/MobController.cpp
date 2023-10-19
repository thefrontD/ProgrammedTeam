// Fill out your copyright notice in the Description page of Project Settings.


#include "MobController.h"
#include "Mob.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardData.h"
#include "ProgrammedTeam.h"

AMobController::AMobController() {
}

void AMobController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);


	auto ControllingMob = Cast<AMob>(GetPawn());
	BBAsset = ControllingMob->GetBBAsset();
	BTAsset = ControllingMob->GetBTAsset();


	if (UseBlackboard(BBAsset, Blackboard)) {
		if (!RunBehaviorTree(BTAsset)) {
			Logger::Print("Error on running BehaviorTree");
		}
	}
	else
		Logger::Print("Error on using Blackboard BehaviorTree");

}

void AMobController::OnUnPossess()
{
	Super::OnUnPossess();


	if (UseBlackboard(BBAsset, Blackboard)) {
		if (!RunBehaviorTree(BTAsset)) {
			Logger::Log("Error on running BehaviorTree");
		}
	}
}

void AMobController::InitController(UBehaviorTree* NewBTAsset, UBlackboardData* NewBBAsset)
{
	BTAsset = NewBTAsset;
	BBAsset = NewBBAsset;
}

void AMobController::OnRepeatTimer()
{
}
