// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TeamProgressMarker.generated.h"

UCLASS()
class PROGRAMMEDTEAM_API ATeamProgressMarker : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATeamProgressMarker();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(VisibleAnywhere)
	class USceneComponent* DSRoot;

	UPROPERTY(VisibleAnywhere)
	class UPatrolComponent* PatrolComponent;

};