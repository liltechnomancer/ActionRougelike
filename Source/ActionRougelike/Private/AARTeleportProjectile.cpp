// Fill out your copyright notice in the Description page of Project Settings.


#include "AARTeleportProjectile.h"

#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

AAARTeleportProjectile::AAARTeleportProjectile()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	HitParticles = CreateDefaultSubobject<UParticleSystem>(TEXT("HitParticles"));

	
	// SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	// SpringArmComp->bUsePawnControlRotation = true;
	// SpringArmComp->SetupAttachment(RootComponent);
}

void AAARTeleportProjectile::BeginPlay()
{
	Super::BeginPlay();
	SphereComp->OnComponentHit.AddDynamic(this, &AAARTeleportProjectile::OnHit);
	GetWorldTimerManager().SetTimer(TimerHandle_TimeToOpenPortal, this, &AAARTeleportProjectile::OpenPortal, 0.8f);
	GetWorldTimerManager().SetTimer(TimerHandle_TimeToTeleport, this, &AAARTeleportProjectile::Teleport_TimeElapsed, 1.0f);
}

void AAARTeleportProjectile::Teleport_TimeElapsed()
{
	APawn* Player = GetInstigator();
	Player->TeleportTo(this->GetActorLocation(), Player->GetActorRotation());
	this->Destroy();
}

void AAARTeleportProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	OpenPortal();
	GetWorldTimerManager().SetTimer(TimerHandle_TimeToTeleport, this, &AAARTeleportProjectile::Teleport_TimeElapsed, 0.2f);
}

void AAARTeleportProjectile::OpenPortal()
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticles, GetActorLocation(), GetActorRotation());
}
