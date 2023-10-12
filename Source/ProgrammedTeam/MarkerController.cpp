// Fill out your copyright notice in the Description page of Project Settings.


#include "MarkerController.h"
#include "NavigationSystem.h"
#include "ProgrammedTeam.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

AMarkerController::AMarkerController() 
{
	RepeatInterval = 3.0f;


}

void AMarkerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (GetWorld() == NULL)
		Logger::Print("Possess Error");
	else
		GetWorld()->GetTimerManager().SetTimer(
			RepeatTimerHandle, 
			this, 
			&AMarkerController::OnRepeatTimer, 
			RepeatInterval, 
			true
		);
}

void AMarkerController::OnUnPossess()
{
	Super::OnUnPossess();
	GetWorld()->GetTimerManager().ClearTimer(RepeatTimerHandle);
}

void AMarkerController::OnRepeatTimer()
{
	Logger::Print("OnRepeatTimer Called");

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
