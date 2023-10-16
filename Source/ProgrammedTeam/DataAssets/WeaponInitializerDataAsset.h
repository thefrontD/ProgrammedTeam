// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WeaponInitializerDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class PROGRAMMEDTEAM_API UWeaponInitializerDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
		USkeletalMesh* WeaponMesh;

	UPROPERTY(EditDefaultsOnly)
		FName MuzzleSocket;

	UPROPERTY(EditDefaultsOnly)
		class UParticleSystem* MuzzleFX;

	UPROPERTY(EditDefaultsOnly)
		class USoundWave* SoundEffect;

	UPROPERTY(EditDefaultsOnly)
		float Damage;

	UPROPERTY(EditDefaultsOnly)
		class UAnimMontageDataAsset* ActingAnimMontageDataAsset;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class ABullet> BulletClass;
};
