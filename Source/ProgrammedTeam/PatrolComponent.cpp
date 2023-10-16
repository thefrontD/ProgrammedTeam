// Fill out your copyright notice in the Description page of Project Settings.


#include "PatrolComponent.h"
#include "PatrolRoute.h"
#include "Components/SplineComponent.h"
#include "ProgrammedTeam.h"

// Sets default values for this component's properties
UPatrolComponent::UPatrolComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	Index = 0;

}


// Called when the game starts
void UPatrolComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPatrolComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPatrolComponent::SetIndexToNext()
{
	//USplineComponent* Spline;

	if (PatrolRoute == nullptr) {
		return;
	}

	if(PatrolRoute->Spline->GetNumberOfSplinePoints() > Index)
		Index++;

	return;
}

bool UPatrolComponent::GetDestination(FVector& out)
{
	if (PatrolRoute == nullptr) {
		out = FVector::ZeroVector;
		return false;
	}

	out = PatrolRoute->Spline->GetLocationAtSplinePoint(Index, ESplineCoordinateSpace::World);

	return true;
}

