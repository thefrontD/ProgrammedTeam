// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Observer.generated.h"

UCLASS()
class PROGRAMMEDTEAM_API AObserver : public ACharacter
{
	GENERATED_BODY()

public:
	AObserver();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


protected:
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
	class ATeamProgressMarker* Marker;

	UPROPERTY(VisibleAnywhere)
	float SpringArmLength = 1000;

};
