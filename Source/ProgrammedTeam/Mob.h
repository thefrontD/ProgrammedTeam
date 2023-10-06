// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProgrammedTeam.h"
#include "GameFramework/Character.h"

#include "Animation/AnimMontage.h"
#include "Mob.generated.h"

UENUM()
enum class MobState : uint8 {
	Idle,
	Acting,
	Dead,
};

struct PlayMontageParameters {
public:
	UAnimMontage* AnimToPlay;
	float PlayRate;
	FString Section;
};

UCLASS()
class PROGRAMMEDTEAM_API AMob : public ACharacter
{
	GENERATED_BODY()

public:
	AMob();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void SetAiming(bool NewAiming);

	//일반공격
	void BeginActionA();

protected:
	UPROPERTY(VisibleAnywhere)
	MobState State;

	UPROPERTY(VisibleAnywhere)
	bool bAiming;

};
