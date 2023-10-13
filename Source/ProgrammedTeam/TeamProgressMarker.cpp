// Fill out your copyright notice in the Description page of Project Settings.


#include "TeamProgressMarker.h"
#include "Components/SceneComponent.h"
#include "PatrolComponent.h"
#include "MarkerController.h"

ATeamProgressMarker::ATeamProgressMarker()
{
	PrimaryActorTick.bCanEverTick = true;

	DSRoot = CreateDefaultSubobject<USceneComponent>("DefaultSceneRoot");
	PatrolComponent = CreateDefaultSubobject<UPatrolComponent>("PatrolComponent");
	//BTAsset = CreateDefaultSubobject<UBehaviorTreeComponent>("UBehaviorTreeComponent");

	AIControllerClass = AMarkerController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void ATeamProgressMarker::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATeamProgressMarker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATeamProgressMarker::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

