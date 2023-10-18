// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TeamProgressMarker.generated.h"

UCLASS()
class PROGRAMMEDTEAM_API ATeamProgressMarker : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATeamProgressMarker();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	bool CheckTeamInBattle();

	void SetMobDestination();

	void GetCenterAndRange(FVector& CenterLocation, float& Range);

private:
	UPROPERTY(VisibleAnywhere)
		class UTPMarkerInitDataAsset* InitDataAsset;

	UPROPERTY(VisibleAnywhere)
		class USceneComponent* DSRoot;

	UPROPERTY(VisibleAnywhere)
		class UPatrolComponent* PatrolComponent;

	UPROPERTY(VisibleAnywhere)
		TArray<FVector> Offsets;

	UPROPERTY(VisibleAnywhere)
		TSubclassOf<class AMob> SpawnClass;

	UPROPERTY(VisibleAnywhere)
		TArray<class AMob*> SpawnedMob;
};
