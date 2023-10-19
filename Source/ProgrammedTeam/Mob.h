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

UCLASS()
class PROGRAMMEDTEAM_API AMob : public ACharacter
{
	GENERATED_BODY()

public:
	AMob();

	void OnConstruction(FTransform const& Transform);

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void SetAiming(bool NewAiming);

	bool GetAiming() const;

	bool IsTargetNull() const;

	void SetTarget(AMob* NewTarget);

	void ApplyDamageTarget();

	virtual float TakeDamage(
		float DamageAmount, 
		struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator,
		AActor* DamageCauser) override;

	class UBehaviorTree* GetBTAsset();

	class UBlackboardData* GetBBAsset();

	void SetDestination(FVector NewDestination);

	void SetTeamNum(const int NewTeamNum) { TeamNum = NewTeamNum; }

	int GetTeamNum() { return TeamNum; }

	FVector GetDestination();

	//일반공격
	void BeginActionA();
	//스킬공격
	void BeginActionB();
	//장비 장착
	void BeginActionC();

protected:
	UPROPERTY(VisibleAnywhere)
	MobState State;

	UPROPERTY(VisibleAnywhere)
	bool bAiming;

	UPROPERTY(VisibleAnywhere)
	UChildActorComponent* Gun;

	UPROPERTY(VisibleAnywhere)
	class UMobInitializerDataAsset* MobInitDataAsset;

	UPROPERTY(VisibleAnywhere)
	AMob* AttackTarget;

	UPROPERTY(VisibleAnywhere)
	float CurrentHP;

	UPROPERTY(VisibleAnywhere)
	FVector Destination;

	UPROPERTY(VisibleAnywhere)
	int TeamNum = 1; /* 0: player, 1: enemy */
};
