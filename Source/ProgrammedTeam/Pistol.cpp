// Fill out your copyright notice in the Description page of Project Settings.


#include "Pistol.h"
#include "ProgrammedTeam.h"
#include "AnimMontageDataAsset.h"

APistol::APistol() {
	static ConstructorHelpers::FObjectFinder<UAnimMontageDataAsset> ActingAnimMontageDataAssetHelper(
		TEXT("/Game/DataAssets/RifleActingDataAsset.RifleActingDataAsset")
	);
	ActingAnimMontageDataAsset = ActingAnimMontageDataAssetHelper.Object;
}

void APistol::BeginActionA() {
	Logger::Log("hello");
	
	return;
}

void APistol::BeginFire()
{
}

void APistol::EndFire()
{
}

void APistol::BeginAiming()
{
}

void APistol::EndAiming()
{
}

void APistol::Reload()
{
}
