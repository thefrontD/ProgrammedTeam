// Fill out your copyright notice in the Description page of Project Settings.


#include "MarkerController.h"
#include "NavigationSystem.h"
#include "ProgrammedTeam.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

AMarkerController::AMarkerController() 
{
	RepeatInterval = 3.0f;

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> FoundBehaviorTree(
		TEXT("/Game/AIAsset/BT_ProgressMarker.BT_ProgressMarker")
	);
	if (FoundBehaviorTree.Succeeded()) {
		BTAsset = FoundBehaviorTree.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBlackboardData> FoundBlackboardData(
		TEXT("/Game/AIAsset/BB_ProgressMarker.BB_ProgressMarker")
	);
	if (FoundBlackboardData.Succeeded()) {
		BBAsset = FoundBlackboardData.Object;
	}
}

void AMarkerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	/*GetWorld()->GetTimerManager().SetTimer(
		RepeatTimerHandle,
		this,
		&AMarkerController::OnRepeatTimer,
		RepeatInterval,
		true
	);*/
	
	if (UseBlackboard(BBAsset, Blackboard)) {
		if (!RunBehaviorTree(BTAsset)) {
			Logger::Log("Error on running BehaviorTree");
		}
	}
}

void AMarkerController::OnUnPossess()
{
	Super::OnUnPossess();
	//GetWorld()->GetTimerManager().ClearTimer(RepeatTimerHandle);
}

void AMarkerController::OnRepeatTimer()
{
	//Logger::Print("OnRepeatTimer Called");

	auto CurrentPawn = GetPawn();
	if (CurrentPawn == nullptr)
		return;

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	if (NavSystem == nullptr)
		return;

	FNavLocation NextLocation;
	if (NavSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, 500.0f, NextLocation)) {
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, NextLocation);

	}

}
