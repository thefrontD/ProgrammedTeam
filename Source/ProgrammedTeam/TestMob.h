// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Mob.h"
#include "TestMob.generated.h"

/**
 * 
 */
UCLASS()
class PROGRAMMEDTEAM_API ATestMob : public AMob
{
	GENERATED_BODY()
public:
	ATestMob();
	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);
	class USpringArmComponent* SpringArm;
	class UCameraComponent* Camera;
private:
	void MoveFB(const float input);
	void MoveLR(const float input);
	void SetControllType(int type);
};