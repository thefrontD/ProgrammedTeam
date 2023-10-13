// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MarkerController.generated.h"

/**
 * 
 */
UCLASS()
class PROGRAMMEDTEAM_API AMarkerController : public AAIController
{
	GENERATED_BODY()
public:
	AMarkerController();
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
private:
	void OnRepeatTimer();
	FTimerHandle RepeatTimerHandle;
	float RepeatInterval;
protected:
	UPROPERTY(VisibleAnywhere)
		class UBehaviorTree* BTAsset;

	UPROPERTY(VisibleAnywhere)
		class UBlackboardData* BBAsset;

};
