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


	FindInitData();
}

void ATeamProgressMarker::BeginPlay()
{
	Super::BeginPlay();
	
	//For Test
	UPTSaveGame* PTSaveGameNew = NewObject<UPTSaveGame>();
	PTSaveGameNew->SavedMobTypes.Add(MobType::Pistol);
	PTSaveGameNew->SavedMobTypes.Add(MobType::SniperRifle);
	PTSaveGameNew->SavedMobTypes.Add(MobType::AssultRifle);
	PTSaveGameNew->SavedMobTypes.Add(MobType::AssultRifle);

	if (!UGameplayStatics::SaveGameToSlot(PTSaveGameNew, "Default", 0)) {
		Logger::Log("save failed");;
	}
	//For Test End

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
			Mob->Init(*(InitDataArray.Find((int)(PTSaveGame->SavedMobTypes[i]))));
			Mob->SetPM(this);
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
	FRotator ActorRotator = GetActorRotation();
	for (int i = 0; i < SpawnedMob.Num(); i++) {
		Logger::Print(ActorLocation + Offsets[i], 1);
		SpawnedMob[i]->SetDestination(ActorLocation + ActorRotator.RotateVector(Offsets[i]));
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
	SpawnedMob.Remove(ptr);
	return;
}

AMob* ATeamProgressMarker::GetClosestEnemy(FVector vector)
{
	AMob* ret = nullptr;

	float dist = -1;
	float newdist;
	for (AMob* enemy : Enemies) {
		if (enemy == nullptr || !(enemy->IsValidLowLevelFast())) {
			Logger::Print("enemy instance invalid", 4);
			continue;
		}
		newdist = FVector::Dist2D(vector, enemy->GetActorLocation());
		if (dist < 0 || dist < newdist) {
			dist = newdist;
			ret = enemy;
		}
	}
	return ret;
}

void ATeamProgressMarker::FindInitData()
{
	static ConstructorHelpers::FObjectFinder<UMobInitializerDataAsset> FoundPistolDataAsset(
		TEXT("/Game/DataAssets/InitData/PistolMobInitDataAsset.PistolMobInitDataAsset")
	);
	if (FoundPistolDataAsset.Succeeded())
		InitDataArray.Add((int)MobType::Pistol, FoundPistolDataAsset.Object);
	static ConstructorHelpers::FObjectFinder<UMobInitializerDataAsset> FoundRifleDataAsset(
		TEXT("/Game/DataAssets/InitData/RifleMobInitDataAsset.RifleMobInitDataAsset")
	);
	if (FoundRifleDataAsset.Succeeded())
		InitDataArray.Add((int)MobType::AssultRifle, FoundRifleDataAsset.Object);
	static ConstructorHelpers::FObjectFinder<UMobInitializerDataAsset> FoundSniperDataAsset(
		TEXT("/Game/DataAssets/InitData/SniperMobInitDataAsset.SniperMobInitDataAsset")
	);
	if (FoundSniperDataAsset.Succeeded())
		InitDataArray.Add((int)MobType::SniperRifle, FoundSniperDataAsset.Object);

	return;
}

