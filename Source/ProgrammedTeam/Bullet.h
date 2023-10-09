// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class PROGRAMMEDTEAM_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:

	UFUNCTION()
		void OnBulletHit(
			const AActor* SelfActor,
			AActor* OtherActor,
			const FVector NormalImpulse,
			const FHitResult& Hit);
	void NotifyHit(
		class UPrimitiveComponent* MyComp,
		AActor* Other,
		class UPrimitiveComponent* OtherComp,
		bool bSelfMoved,
		FVector HitLocation,
		FVector HitNormal,
		FVector NormalImpulse,
		const FHitResult& Hit);


private:
	UPROPERTY(VisibleAnywhere)
		class USphereComponent* Collider;

	UPROPERTY(VisibleAnywhere)
		class UParticleSystemComponent* Tracer;

	UPROPERTY(EditDefaultsOnly)
		class UParticleSystem* HitEffect;

	UPROPERTY(VisibleAnywhere)
		class UProjectileMovementComponent* Movement;
};
