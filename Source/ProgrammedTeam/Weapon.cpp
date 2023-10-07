// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "AnimMontageDataAsset.h"

AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> TheWeaponMesh(
		TEXT("/Game/MilitaryWeapDark/Weapons/Assault_Rifle_B.Assault_Rifle_B")
	);
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");
	if (TheWeaponMesh.Succeeded()) {
		Mesh->SetSkeletalMesh(TheWeaponMesh.Object);
	}
	SetRootComponent(Mesh);

	static ConstructorHelpers::FObjectFinder<UAnimMontageDataAsset> TheDataAsset(
		TEXT("/Game/DataAssets/RifleActingDataAsset.RifleActingDataAsset")
	);

	if (TheDataAsset.Succeeded()) {
		ActingAnimMontageDataAsset = TheDataAsset.Object;
	}
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

