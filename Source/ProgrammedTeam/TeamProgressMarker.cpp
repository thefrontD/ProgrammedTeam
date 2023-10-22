// Fill out your copyright notice in the Description page of Project Settings.


#include "TeamProgressMarker.h"
#include "Components/SceneComponent.h"
#include "PatrolComponent.h"
#include "MarkerController.h"
#include "PTSaveGame.h"
#include "MobTypeEnum.h"
#include "Mob.h"
#include "Kismet/GameplayStatics.h"
#include "ProgrammedTeam.h"
#include "DataAssets/TPMarkerInitDataAsset.h"
#include "GameFramework/CharacterMovementComponent.h"

ATeamProgressMarker::ATeamProgressMarker()
{
	PrimaryActorTick.bCanEverTick = false;

	static ConstructorHelpers::FObjectFinder<UTPMarkerInitDataAsset> FoundInitDataAsset(
		TEXT("/Game/DataAssets/InitData/TPMarkerInitDataAsset.TPMarkerInitDataAsset")
		);
	if (FoundInitDataAsset.Succeeded()) {
		InitDataAsset = FoundInitDataAsset.Object;

		GetMesh()->SetSkeletalMesh(InitDataAsset->Mesh);
		SpawnClass = InitDataAsset->SpawnClass;

	}

	DSRoot = CreateDefaultSubobject<USceneComponent>("DefaultSceneRoot");
	PatrolComponent = CreateDefaultSubobject<UPatrolComponent>("PatrolComponent");
	//BTAsset = CreateDefaultSubobject<UBehaviorTreeComponent>("UBehaviorTreeComponent");

	AIControllerClass = AMarkerController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	GetCharacterMovement()->MaxWalkSpeed = 2000;
		

	//Class'/Script/ProgrammedTeam.Mob'
}

void ATeamProgressMarker::BeginPlay()
{
	Super::BeginPlay();
	

	UPTSaveGame* PTSaveGameNew = NewObject<UPTSaveGame>();
	PTSaveGameNew->SavedMobTypes.Add(MobType::Pistol);
	PTSaveGameNew->SavedMobTypes.Add(MobType::SniperRifle);
	PTSaveGameNew->SavedMobTypes.Add(MobType::AssultRifle);
	PTSaveGameNew->SavedMobTypes.Add(MobType::AssultRifle);


	if (!UGameplayStatics::SaveGameToSlot(PTSaveGameNew, "Default", 0)) {
		Logger::Log("save failed");;
	}


	FString SaveSlotName = "Default";
	UPTSaveGame* PTSaveGame = Cast<UPTSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0));


	Offsets.Add(FVector(0, 100, 0));
	Offsets.Add(FVector(0, 200, 0));
	Offsets.Add(FVector(0, -100, 0));
	Offsets.Add(FVector(0, -200, 0));


	for (int i = 0; i < PTSaveGame->SavedMobTypes.Num(); i++) {
		if (Offsets.Num() > i) {
			FTransform transform;
			transform.SetLocation(GetActorLocation() + Offsets[i]);
			auto Mob = GetWorld()->SpawnActor<AMob>(SpawnClass, transform);
			Mob->SetTeamNum(0);
			Mob->SingleDelegateOneParam.BindUFunction(this, "RemoveMobFromArray");
			SpawnedMob.Add(Mob);
		}
	}
}

void ATeamProgressMarker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATeamProgressMarker::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

bool ATeamProgressMarker::CheckTeamInBattle()
{
	bool bResult = false;

	for (AMob* Mob : SpawnedMob) {
		bResult |= !(Mob->IsTargetNull());
	}

	//if (bResult)
	//	Logger::Print("InBattle true");
	return bResult;
}

bool ATeamProgressMarker::CheckTeamInPosition()
{

	bool bResult = true;

	for (AMob* Mob : SpawnedMob) {
		if (!(Mob->IsNearDestination()))
		bResult = (bResult && (Mob->IsNearDestination()));
	}

	return bResult;
}

void ATeamProgressMarker::SetMobDestination()
{
	FVector ActorLocation = GetActorLocation();
	for (int i = 0; i < SpawnedMob.Num(); i++) {
		Logger::Print(ActorLocation + Offsets[i], 1);
		SpawnedMob[i]->SetDestination(ActorLocation + Offsets[i]);
	}
}

void ATeamProgressMarker::GetCenterAndRange(FVector& CenterLocation, float& Range)
{
	FVector SumVector = FVector::ZeroVector;

	for (AMob* Mob : SpawnedMob) {
		SumVector += Mob->GetActorLocation();
	}
	CenterLocation = SumVector / SpawnedMob.Num();

	float newRange = 0.0f;
	for (AMob* Mob : SpawnedMob) {
		float calc = FVector::DistXY(FVector::ZeroVector, CenterLocation - Mob->GetActorLocation());
		if (newRange < calc)
			newRange = calc;
	}
	Range = newRange + 50.0f;

	return;
}

void ATeamProgressMarker::RemoveMobFromArray(AMob* ptr)
{
	//Logger::Print("Team Mob Removed");
	//Logger::Print(SpawnedMob.Remove(ptr));
	return;
}

