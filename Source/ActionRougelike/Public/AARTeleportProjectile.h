// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AARProjectileBase.h"
#include "AARTeleportProjectile.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROUGELIKE_API AAARTeleportProjectile : public AAARProjectileBase
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	AAARTeleportProjectile();
	
protected:
	UPROPERTY(EditAnywhere)
	UParticleSystem* HitParticles;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	FTimerHandle TimerHandle_TimeToTeleport;
	FTimerHandle TimerHandle_TimeToOpenPortal;
	
	void Teleport_TimeElapsed();
	void OpenPortal();
};
