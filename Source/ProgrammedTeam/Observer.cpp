// Fill out your copyright notice in the Description page of Project Settings.


#include "Observer.h"
#include "Engine/World.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TeamProgressMarker.h"

AObserver::AObserver()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->bDoCollisionTest = false;
	SpringArm->TargetArmLength = 1500.0f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);


}

void AObserver::BeginPlay()
{
	Super::BeginPlay();
	TSubclassOf<ATeamProgressMarker> ClassToFind;
	ClassToFind = ATeamProgressMarker::StaticClass();
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ClassToFind, FoundActors);
	if (FoundActors.Num() != 0) {
		Marker = Cast<ATeamProgressMarker>(FoundActors[0]);
	}

}

void AObserver::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CenterLocation;
	float Range;
	Marker->GetCenterAndRange(CenterLocation, Range);
	SetActorLocation(CenterLocation);
	SpringArm->TargetArmLength = 1000;//Range * 5;

}

void AObserver::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

