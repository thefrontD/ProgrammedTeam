// Fill out your copyright notice in the Description page of Project Settings.


#include "TeamProgressMarker.h"
#include "Components/SceneComponent.h"
#include "PatrolComponent.h"
#include "MarkerController.h"

// Sets default values
ATeamProgressMarker::ATeamProgressMarker()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DSRoot = CreateDefaultSubobject<USceneComponent>("DefaultSceneRoot");
	PatrolComponent = CreateDefaultSubobject<UPatrolComponent>("PatrolComponent");
	//BTAsset = CreateDefaultSubobject<UBehaviorTreeComponent>("UBehaviorTreeComponent");
}

// Called when the game starts or when spawned
void ATeamProgressMarker::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATeamProgressMarker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATeamProgressMarker::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

