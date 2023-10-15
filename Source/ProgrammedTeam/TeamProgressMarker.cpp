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
#include "TPMarkerInitDataAsset.h"

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


	Offsets.Add(FVector(200, 200, 0));
	Offsets.Add(FVector(-200, 200, 0));
	Offsets.Add(FVector(200, -200, 0));
	Offsets.Add(FVector(-200, -200, 0));


	for (int i = 0; i < PTSaveGame->SavedMobTypes.Num(); i++) {
		if (Offsets.Num() > i) {
			FTransform transform;
			transform.SetLocation(GetActorLocation() + Offsets[i]);
			GetWorld()->SpawnActor<AMob>(SpawnClass, transform);
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

