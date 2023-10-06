// Fill out your copyright notice in the Description page of Project Settings.



#include "Mob.h"
#include "MobAnimInstance.h"

AMob::AMob()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM_BODY(
		TEXT("/Game/Skeletal_Meshes/Manequin/SK_Mannequin.SK_Mannequin")
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

	Logger::Log("false");	
	if (ABP_Mob.Succeeded()) {
		Logger::Log("true");
		CharacterMesh->SetAnimInstanceClass(ABP_Mob.Class);
	}

	//Cast<UMobAnimInstance>(CharacterMesh->GetAnimInstance())->SetAiming(false);
	//SetAiming(false);
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
	UMobAnimInstance* AnimInstance = Cast<UMobAnimInstance>(GetMesh()->GetAnimInstance());
	//AnimInstance->SetAiming(NewAiming);
}

void AMob::BeginActionA()
{
	//
}

