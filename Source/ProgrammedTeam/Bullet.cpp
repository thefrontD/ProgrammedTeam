// Fill out your copyright notice in the Description page of Project Settings.

#include "Bullet.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ProgrammedTeam.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InitialLifeSpan = 2;

	Collider = CreateDefaultSubobject<USphereComponent>("Collider");
	SetRootComponent(Collider);

	Tracer = CreateDefaultSubobject<UParticleSystemComponent>("Tracer");
	Tracer->SetupAttachment(Collider);

	Movement = CreateDefaultSubobject<UProjectileMovementComponent>("Movement");
	Movement->InitialSpeed = 10000;
	Movement->bRotationFollowsVelocity = true;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> FoundParticleSystem(
		TEXT("/Game/MilitaryWeapDark/FX/P_AssaultRifle_Tracer_01.P_AssaultRifle_Tracer_01")
	);
	if (FoundParticleSystem.Succeeded()) {
		Tracer->SetTemplate(FoundParticleSystem.Object);
	}

}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABullet::OnBulletHit(
	const AActor* SelfActor, 
	AActor* OtherActor, 
	const FVector NormalImpulse, 
	const FHitResult& Hit
)
{
	UGameplayStatics::ApplyDamage
	(
		OtherActor,
		1,
		GetInstigatorController(),
		GetOwner(),
		UDamageType::StaticClass()
	);

	Logger::Log("hit");

}

void ABullet::NotifyHit(
	UPrimitiveComponent* MyComp, 
	AActor* Other, 
	UPrimitiveComponent* OtherComp, 
	bool bSelfMoved, 
	FVector HitLocation, 
	FVector HitNormal, 
	FVector NormalImpulse, 
	const FHitResult& Hit
)
{
	Super::NotifyHit(
		MyComp,
		Other,
		OtherComp,
		bSelfMoved,
		HitLocation,
		HitNormal,
		NormalImpulse,
		Hit);


	float Damage = 1;
	UGameplayStatics::ApplyDamage
	(
		Other,
		Damage,
		GetInstigatorController(),
		GetOwner(),
		UDamageType::StaticClass()
	);

	if (HitEffect != nullptr) {
		UGameplayStatics::SpawnEmitterAttached(
			HitEffect,
			Hit.GetComponent(),
			NAME_None,
			Hit.Location,
			Hit.Normal.Rotation(),
			EAttachLocation::Type::KeepWorldPosition,
			false,
			EPSCPoolMethod::AutoRelease
		);
	}

	Logger::Log("hit");

	Destroy();

}

