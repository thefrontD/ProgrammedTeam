// Fill out your copyright notice in the Description page of Project Settings.


#include "TestMob.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"


ATestMob::ATestMob() {
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SetControllType(1);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

void ATestMob::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAxis(TEXT("MoveFB"), this, &ATestMob::MoveFB);
	PlayerInputComponent->BindAxis(TEXT("MoveLR"), this, &ATestMob::MoveLR);
	PlayerInputComponent->BindAction(TEXT("ActionA"), EInputEvent::IE_Pressed, this, &ATestMob::BeginActionA);
	PlayerInputComponent->BindAction(TEXT("ActionB"), EInputEvent::IE_Pressed, this, &ATestMob::BeginActionB);
	PlayerInputComponent->BindAction(TEXT("ActionC"), EInputEvent::IE_Pressed, this, &ATestMob::BeginActionC);

}

void ATestMob::MoveFB(const float ForwardInput) {

	AddMovementInput(Camera->GetForwardVector(), ForwardInput);
}

void ATestMob::MoveLR(const float LeftInput)
{

	AddMovementInput(Camera->GetRightVector(), -LeftInput);
}

void ATestMob::SetControllType(int type)
{
	switch (type)
	{
	case 0:
		SpringArm->TargetArmLength = 400.0f;
		SpringArm->bUsePawnControlRotation = true;
		SpringArm->bInheritPitch = true;
		SpringArm->bInheritRoll = true;
		SpringArm->bInheritYaw = true;
		bUseControllerRotationYaw = false;
		break;
	case 1:
		SpringArm->SetRelativeLocation(FVector::UpVector * 50);
		SpringArm->SetRelativeRotation(FRotator(-15, 0,0));
		SpringArm->TargetArmLength = 400.0f;
		SpringArm->bUsePawnControlRotation = false;
		SpringArm->bInheritPitch = false;
		SpringArm->bInheritRoll = false;
		SpringArm->bInheritYaw = false;
		bUseControllerRotationYaw = false;
		GetCharacterMovement()->bOrientRotationToMovement = true;
		break;
	default:
		break;
	}
}
