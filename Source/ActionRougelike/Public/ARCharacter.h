// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ARCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UARInteractionComponent;
class UAnimMontage;

UCLASS()
class ACTIONROUGELIKE_API AARCharacter : public ACharacter
{
	GENERATED_BODY()

protected: 

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor>ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Attack")
	UAnimMontage* AttackAnim;

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor>BlackHoleClass;

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor>DashClass;
	
	FTimerHandle TimerHandle_PrimaryAttack;

public:
	// Sets default values for this character's properties
	AARCharacter();

protected:

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere)
	UARInteractionComponent* InteractionComp;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void FireProjectile(TSubclassOf<AActor> Projectile);
	void PrimaryAttack_TimeElapsed();
	void PrimaryAttack();
	void SecondaryAttack_TimeElapsed();
	void SecondaryAttack();
	void DashAttack_TimeElapsed();
	void DashAttack();
	void PrimaryInteract();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
