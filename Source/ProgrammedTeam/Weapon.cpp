// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/AudioComponent.h"
#include "ProgrammedTeam.h"
#include "DataAssets/AnimMontageDataAsset.h"
#include "Bullet.h"
#include "DataAssets/WeaponInitializerDataAsset.h"

AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = false;


	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");
	SetRootComponent(Mesh);
	MuzzleFlash = CreateDefaultSubobject<UParticleSystemComponent>("MuzzleFlash");
	GunshotSound = CreateDefaultSubobject<UAudioComponent>("GunshotSound");

	static ConstructorHelpers::FObjectFinder<UWeaponInitializerDataAsset> FoundInitDataAsset(
		TEXT("/Game/DataAssets/InitData/RifleWeaponInitDataAsset.RifleWeaponInitDataAsset")
	);

	if (FoundInitDataAsset.Succeeded()) {
		Logger::Log("FoundInitDataAsset.Succeeded()");
		WeaponInitDataAsset = FoundInitDataAsset.Object;

		Mesh->SetSkeletalMesh(WeaponInitDataAsset->WeaponMesh);

		ActingAnimMontageDataAsset = WeaponInitDataAsset->ActingAnimMontageDataAsset;

		MuzzleFlash->SetTemplate(WeaponInitDataAsset->MuzzleFX);
		MuzzleFlash->SetAutoActivate(false);
		GunshotSound->SetSound(WeaponInitDataAsset->SoundEffect);
		GunshotSound->SetAutoActivate(false);
	}
	

}

void AWeapon::OnConstruction(FTransform const& Transform)
{
	FAttachmentTransformRules const Rules(EAttachmentRule::SnapToTarget, true);
	MuzzleFlash->AttachToComponent(GetRootComponent(), Rules, WeaponInitDataAsset->MuzzleSocket);
	GunshotSound->AttachToComponent(GetRootComponent(), Rules, WeaponInitDataAsset->MuzzleSocket);
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FStateAnimMontageData AWeapon::GetAnimMontage(int index)
{
	if (ActingAnimMontageDataAsset->List.Num() <= index) {
		Logger::Log("IndexOutOfBound");
		return FStateAnimMontageData();
	}
	Logger::Log(ActingAnimMontageDataAsset->List.Num());
	return ActingAnimMontageDataAsset->List[index];
}

void AWeapon::BeginActionA()
{
	MuzzleFlash->Activate(true);
	GunshotSound->Activate(true);

	//FTransform Muzzle = Mesh->GetSocketTransform(WeaponInitDataAsset->MuzzleSocket);

	//Muzzle.SetLocation(Muzzle.GetLocation() + Muzzle.GetRotation().GetForwardVector() * 25);

	//FActorSpawnParameters SpawnParameters;

	//SpawnParameters.Owner = this;
	//SpawnParameters.Instigator = GetInstigator();

	//GetWorld()->SpawnActor<AActor>(WeaponInitDataAsset->BulletClass, Muzzle, SpawnParameters);
}

void AWeapon::BeginActionB()
{

}

void AWeapon::BeginActionC()
{

}


