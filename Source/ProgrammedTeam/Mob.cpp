// Fill out your copyright notice in the Description page of Project Settings.



#include "Mob.h"
#include "Pistol.h"
#include "MobAnimInstance.h"

AMob::AMob()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM_BODY(
		TEXT("/Game/AnimStarterPack/UE4_Mannequin/Mesh/SK_Mannequin.SK_Mannequin")
	);

	auto CharacterMesh = GetMesh();
	if (SM_BODY.Succeeded()) {
		CharacterMesh->SetSkeletalMesh(SM_BODY.Object);
		CharacterMesh->AddRelativeLocation(FVector(0, 0, -80));
		CharacterMesh->SetRelativeRotation(FRotator(0, -90, 0));
		CharacterMesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	}

	State = MobState::Idle;
	bAiming = false;

	static ConstructorHelpers::FClassFinder<UAnimInstance> ABP_Mob(
		TEXT("/Game/Animations/Firearms/Pistol/ABP_Pistol.ABP_Pistol_C")
	);

	if (ABP_Mob.Succeeded()) {
		CharacterMesh->SetAnimInstanceClass(ABP_Mob.Class);
	}



	//initialize gun component
	Gun = CreateDefaultSubobject<UChildActorComponent>("Gun");
	Gun->SetupAttachment(GetRootComponent());

	static ConstructorHelpers::FClassFinder<APistol> WPClass(
		TEXT("/Script/ProgrammedTeam.Pistol")
	);
	WeaponClass = WPClass.Class;


	//Cast<UMobAnimInstance>(CharacterMesh->GetAnimInstance())->SetAiming(false);
}

void AMob::OnConstruction(FTransform const& Transform) {
	Super::OnConstruction(Transform);


	FAttachmentTransformRules const Rules(EAttachmentRule::SnapToTarget, true);
	Gun->AttachToComponent(GetMesh(), Rules, FName(TEXT("hand_rSocket")));
	Gun->SetChildActorClass(WeaponClass);
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
			if (auto ActableOne = Cast<IActableOneInterface>(Gun->GetChildActor())) {
				//GetMesh()->GetAnimInstance()->Montage_Play()
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

