// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ARInteractInterface.h"
#include "AARItemChest.generated.h"

class UStaticMeshComponent;

UCLASS()
class ACTIONROUGELIKE_API AAARItemChest : public AActor, public IARInteractInterface
{
	GENERATED_BODY()

    void Interact_Implementation(APawn* InstagatorPawn);
	
public:	

	UPROPERTY(EditAnywhere)
	float TargetPitch;
	// Sets default values for this actor's properties
	AAARItemChest();

protected:

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* LidMesh;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:


};
