// Fill out your copyright notice in the Description page of Project Settings.


#include "MobAnimInstance.h"

void UMobAnimInstance::NativeUpdateAnimation(float DeltaSeconds) {
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();

	if (IsValid(Pawn)) {
		Speed = Pawn->GetVelocity().Size();
	}
}

void UMobAnimInstance::SetAiming(bool aiming)
{
	this->bAiming = aiming;
}
