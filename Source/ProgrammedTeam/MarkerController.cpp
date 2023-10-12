// Fill out your copyright notice in the Description page of Project Settings.


#include "MarkerController.h"

AMarkerController::AMarkerController() 
{
	RepeatInterval = 0.5f;
}

void AMarkerController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);
	GetWorld()->GetTimerManager().SetTimer(RepeatTimerHandle, this, &AMarkerController::OnRepeatTimer, RepeatInterval, true);
}

void AMarkerController::UnPossess()
{
	Super::UnPossess();
	GetWorld()->GetTimerManager().ClearTimer(RepeatTimerHandle);
}

void AMarkerController::OnRepeatTimer()
{
}
