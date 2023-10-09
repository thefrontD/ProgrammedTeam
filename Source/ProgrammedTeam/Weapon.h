// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AnimMontageGettableInterface.h"
#include "ActableOneInterface.h"
#include "Weapon.generated.h"

UCLASS()
class PROGRAMMEDTEAM_API AWeapon : 
	public AActor,
	public IAnimMontageGettableInterface,
	public IActableOneInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	struct FStateAnimMontageData GetAnimMontage(int index) override;
	void BeginActionA() override;
	void BeginActionB() override;
	void BeginActionC() override;
	void OnConstruction(FTransform const& Transform) override;

protected:
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere)
	FString MeshRef;

	UPROPERTY(VisibleAnywhere)
	class UParticleSystemComponent* MuzzleFlash;

	UPROPERTY(VisibleAnywhere)
	class UAudioComponent* GunshotSound;

	UPROPERTY(VisibleAnywhere)
	class UAnimMontageDataAsset* ActingAnimMontageDataAsset;

	UPROPERTY(VisibleAnywhere)
	class UWeaponInitializerDataAsset* WeaponInitDataAsset;
};
