// Fill out your copyright notice in the Description page of Project Settings.


#include "AARItemChest.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
AAARItemChest::AAARItemChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;

	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LidMesh"));
	LidMesh->SetupAttachment(BaseMesh);

	TargetPitch = 110;
}

// Called when the game starts or when spawned
void AAARItemChest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAARItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAARItemChest::Interact_Implementation(APawn* InstagatorPawn)
{
	LidMesh->SetRelativeRotation(FRotator(110, 0, 0));
}