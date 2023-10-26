// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MobController.generated.h"

/**
 * 
 */
UCLASS()
class PROGRAMMEDTEAM_API AMobController : public AAIController
{
	GENERATED_BODY()
public:
	AMobController();
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
	//void InitController(class UBehaviorTree* BTAsset, class UBlackboardData* BBAsset);
private:
	void OnRepeatTimer();
protected:
	UPROPERTY(VisibleAnywhere)
		class UBehaviorTree* BTAsset;

	UPROPERTY(VisibleAnywhere)
		class UBlackboardData* BBAsset;

	class UBehaviorTreeComponent* BehaviorTreeComponent;
};
