// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AARProjectileBase.h"
#include "GameFramework/Actor.h"
#include "ARMagicProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;

UCLASS()
class ACTIONROUGELIKE_API AARMagicProjectile : public AAARProjectileBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AARMagicProjectile();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
