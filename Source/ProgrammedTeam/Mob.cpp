// Fill out your copyright notice in the Description page of Project Settings.

#include "Mob.h"
#include "Pistol.h"
#include "DataAssets/Structs/StateAnimMontageData.h"
#include "DataAssets/MobInitializerDataAsset.h"
#include "ActableOneInterface.h"
#include "MobAnimInstance.h"
//#include "GameFramework/CharacterMovementComponent.h"
#include "MobController.h"

AMob::AMob()
{
	PrimaryActorTick.bCanEverTick = true;
	auto CharacterMesh = GetMesh();


	//initialize gun component
	Gun = CreateDefaultSubobject<UChildActorComponent>("Gun");
	Gun->SetupAttachment(GetRootComponent());


	static ConstructorHelpers::FObjectFinder<UMobInitializerDataAsset> FoundInitDataAsset(
		TEXT("/Game/DataAssets/InitData/RifleMobInitDataAsset.RifleMobInitDataAsset")
	);


	if (FoundInitDataAsset.Succeeded()) {
		MobInitDataAsset = FoundInitDataAsset.Object;

		CharacterMesh->SetSkeletalMesh(MobInitDataAsset->MobMesh);
		CharacterMesh->AddRelativeLocation(FVector(0, 0, -80));
		CharacterMesh->SetRelativeRotation(FRotator(0, -90, 0));
		CharacterMesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);

		CharacterMesh->SetAnimInstanceClass(MobInitDataAsset->MobABP);

		CurrentHP = MobInitDataAsset->MaxHP;
		Range = MobInitDataAsset->Range;
		Damage = MobInitDataAsset->Damage;
		AttackDelay = MobInitDataAsset->AttackDelay;
	}
	//CharacterMovement->Set

	State = MobState::Idle;
	bAiming = false;
	bInBattle = false;


	AIControllerClass = AMobController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

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

void AMob::DestroyProcess()
{
	if (SingleDelegateOneParam.IsBound())
		SingleDelegateOneParam.Execute(this);
	//SetLifeSpan(1.0f);
	Destroy();
	return;
}



void AMob::BeginPlay()
{
	Super::BeginPlay();



	//GetController
	//MobInitDataAsset->BTAsset
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

bool AMob::GetAiming() const
{
	return bAiming;
}

bool AMob::IsTargetNull() const
{
	return AttackTarget == nullptr;
}

void AMob::SetTarget(AMob* NewTarget)
{
	AttackTarget = NewTarget;
}

void AMob::ApplyDamageTarget()
{
	FDamageEvent DamageEvent;
	if (AttackTarget != nullptr) {
		AttackTarget->TakeDamage(
			MobInitDataAsset->Damage,
			DamageEvent,
			GetController(),
			this);
	}
}

float AMob::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	CurrentHP -= FinalDamage;

	if (CurrentHP < 0) {
		State = MobState::Dead;
		DestroyProcess();
	}

	return 0.0f;
}

UBehaviorTree* AMob::GetBTAsset()
{
	return MobInitDataAsset->BTAsset;
}

UBlackboardData* AMob::GetBBAsset()
{
	return MobInitDataAsset->BBAsset;
}

void AMob::SetDestination(FVector NewDestination)
{
	Destination = NewDestination;
	float diff = (NewDestination - GetActorLocation()).Size();
	if (diff > AcceptableRadius)
		bNearDestination = false;
	else
		bNearDestination = true;
	return;
}

FVector AMob::GetDestination()
{
	return Destination;
}

void AMob::BeginActionA()
{
	if (Gun != nullptr) {
		Logger::Log("BeginActionA");

		if (bAiming) {
			if (auto AMGettable = Cast<IAnimMontageGettableInterface>(Gun->GetChildActor())) {
				FStateAnimMontageData data = AMGettable->GetAnimMontage(0);
				Logger::Log(data.Montage->GetFName().ToString()); //AM_Fire_Rifle 정상적으로 출력
				//PlayAnimMontage(data.Montage);
				GetMesh()->GetAnimInstance()->Montage_Play(data.Montage, data.PlayRate);

				auto ActableOne = Cast<IActableOneInterface>(Gun->GetChildActor());
				ActableOne->BeginActionA();

				ApplyDamageTarget();
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

