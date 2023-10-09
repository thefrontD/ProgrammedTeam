// Fill out your copyright notice in the Description page of Project Settings.



#include "Mob.h"
#include "Pistol.h"
#include "StateAnimMontageData.h"
#include "MobInitializerDataAsset.h"
#include "ActableOneInterface.h"
#include "MobAnimInstance.h"

AMob::AMob()
{
	PrimaryActorTick.bCanEverTick = true;
	auto CharacterMesh = GetMesh();


	//initialize gun component
	Gun = CreateDefaultSubobject<UChildActorComponent>("Gun");
	Gun->SetupAttachment(GetRootComponent());


	static ConstructorHelpers::FObjectFinder<UMobInitializerDataAsset> FoundInitDataAsset(
		TEXT("/Game/DataAssets/RifleMobInitDataAsset.RifleMobInitDataAsset")
	);


	if (FoundInitDataAsset.Succeeded()) {
		MobInitDataAsset = FoundInitDataAsset.Object;

		CharacterMesh->SetSkeletalMesh(MobInitDataAsset->MobMesh);
		CharacterMesh->AddRelativeLocation(FVector(0, 0, -80));
		CharacterMesh->SetRelativeRotation(FRotator(0, -90, 0));
		CharacterMesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);

		CharacterMesh->SetAnimInstanceClass(MobInitDataAsset->MobABP);
	}


	State = MobState::Idle;
	bAiming = false;


	//Cast<UMobAnimInstance>(CharacterMesh->GetAnimInstance())->SetAiming(false);
}

void AMob::OnConstruction(FTransform const& Transform) {
	Super::OnConstruction(Transform);


	FAttachmentTransformRules const Rules(EAttachmentRule::SnapToTarget, true);
	Gun->AttachToComponent(GetMesh(), Rules, MobInitDataAsset->GunSocket);
	Gun->SetChildActorClass(MobInitDataAsset->GunClass);
	Gun->CreateChildActor();
	Gun->GetChildActor()->SetOwner(this);
	Gun->GetChildActor()->SetInstigator(this);

}



void AMob::BeginPlay()
{
	Super::BeginPlay();
}

void AMob::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMob::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMob::SetAiming(bool NewAiming)
{
	auto AnimInstance = Cast<UMobAnimInstance>(GetMesh()->GetAnimInstance());
	AnimInstance->SetAiming(NewAiming);
}

void AMob::BeginActionA()
{
	if (Gun != nullptr) {
		Logger::Log("BeginActionA");

		if (bAiming) {
			if (auto AMGettable = Cast<IAnimMontageGettableInterface>(Gun->GetChildActor())) {
				FStateAnimMontageData data = AMGettable->GetAnimMontage(0);
				Logger::Log(data.Montage->GetFName().ToString()); //AM_Fire_Rifle 정상적으로 출력
				GetMesh()->GetAnimInstance()->Montage_Play(data.Montage, data.PlayRate);

				auto ActableOne = Cast<IActableOneInterface>(Gun->GetChildActor());
				ActableOne->BeginActionA();
			}
		}
	}
}
void AMob::BeginActionB()
{
	Logger::Log("BeginActionB");
}

void AMob::BeginActionC()
{
	Logger::Log("BeginActionC");
	bAiming = !bAiming;
	SetAiming(bAiming);
}

