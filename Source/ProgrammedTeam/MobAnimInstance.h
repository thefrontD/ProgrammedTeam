// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MobAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROGRAMMEDTEAM_API UMobAnimInstance : 
	public UAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	void SetAiming(bool NewAiming);

public:
	UPROPERTY(BlueprintReadOnly)
	float Speed;
	UPROPERTY(BlueprintReadOnly)
	bool bAiming;
};
