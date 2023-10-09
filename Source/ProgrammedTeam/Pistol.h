// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "ActableOneInterface.h"
#include "Pistol.generated.h"

/**
 * 
 */
UCLASS()
class PROGRAMMEDTEAM_API APistol : 
	public AWeapon
{
	GENERATED_BODY()

public:
	APistol();

private:
	//void BeginActionA() override;


private:
	virtual void BeginFire();
	virtual void EndFire();
	virtual void BeginAiming();
	virtual void EndAiming();
	virtual void Reload();

private:

	UPROPERTY(VisibleAnywhere)
		class UParticleSystemComponent* AmmoEjection;


	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess))
		FName AmmoEjectionSocket;
};
