// Fill out your copyright notice in the Description page of Project Settings.


#include "ARCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ARInteractionComponent.h"
// Sets default values
AARCharacter::AARCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);


	
	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	InteractionComp = CreateDefaultSubobject<UARInteractionComponent>("InteractionComp");

	GetCharacterMovement()->bOrientRotationToMovement = true;

	bUseControllerRotationYaw = false;
}

// Called when the game starts or when spawned
void AARCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AARCharacter::MoveForward(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	AddMovementInput(ControlRot.Vector(), Value);
}

void AARCharacter::MoveRight(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	// X - Forward (Red)
	// Y - Right (Green)
	// Z - Up (Blue)

	FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);

	AddMovementInput(RightVector, Value);
}


void AARCharacter::FireProjectile(TSubclassOf<AActor> Projectile)
{
	FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");


	// GetCamera
	// APlayerCameraManager *camManager = GetWorld()->GetFirstPlayerController()->PlayerCameraManager
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);
	ObjectQueryParams.AddObjectTypesToQuery(ECC_PhysicsBody);
	
	FVector CameraLocation = CameraComp->GetComponentLocation();
	FRotator CameraRotation = CameraComp->GetComponentRotation();

	FVector End = CameraLocation + (CameraRotation.Vector() * 10000);
	FHitResult Hit;

	bool bBlockingHit = GetWorld()->LineTraceSingleByObjectType(Hit, CameraLocation, End, ObjectQueryParams);

	FColor LineColor = bBlockingHit ? FColor::Green : FColor::Red;
	
	DrawDebugLine(GetWorld(), CameraLocation, End, LineColor, false, 2.0f, 0, 2.0f);
	FRotator ToHitRotation = (Hit.ImpactPoint - HandLocation).Rotation();
	DrawDebugLine(GetWorld(), HandLocation, Hit.ImpactPoint, LineColor, false, 2.0f, 0, 2.0f);

	// Ternary to decide angle. 
	FTransform SpawnTM = FTransform(bBlockingHit ? ToHitRotation : GetControlRotation(), HandLocation);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	SpawnParams.Instigator = this;

	GetWorld()->SpawnActor<AActor>(Projectile, SpawnTM, SpawnParams);
}

void AARCharacter::PrimaryAttack()
{
	UE_LOG(LogTemp, Log, TEXT("Primary Attack Called"));
	PlayAnimMontage(AttackAnim); 
	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &AARCharacter::PrimaryAttack_TimeElapsed, 0.2f);
}

void AARCharacter::PrimaryAttack_TimeElapsed()
{
	UE_LOG(LogTemp, Warning, TEXT("I have gotten to the secret spot"));
	FireProjectile(ProjectileClass);
}

void AARCharacter::SecondaryAttack()
{
	PlayAnimMontage(AttackAnim); 
	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &AARCharacter::SecondaryAttack_TimeElapsed, 0.2f);
}

void AARCharacter::SecondaryAttack_TimeElapsed()
{
	UE_LOG(LogTemp, Warning, TEXT("I have gotten to the secret black hole spot"));
	FireProjectile(BlackHoleClass);
}

void AARCharacter::PrimaryInteract()
{
	if (InteractionComp) 
	{
		InteractionComp->PrimaryInteract();
	}

}

// Called every frame
void AARCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	// -- Rotation Visualization -- //
	const float DrawScale = 100.0f;
	const float Thickness = 5.0f;

	FVector LineStart = GetActorLocation();
	// Offset to the right of pawn
	LineStart += GetActorRightVector() * 100.0f;
	// Set line end in direction of the actor's forward
	FVector ActorDirection_LineEnd = LineStart + (GetActorForwardVector() * 100.0f);
	// Draw Actor's Direction
	DrawDebugDirectionalArrow(GetWorld(), LineStart, ActorDirection_LineEnd, DrawScale, FColor::Yellow, false, 0.0f, 0, Thickness);

	FVector ControllerDirection_LineEnd = LineStart + (GetControlRotation().Vector() * 100.0f);
	// Draw 'Controller' Rotation ('PlayerController' that 'possessed' this character)
	DrawDebugDirectionalArrow(GetWorld(), LineStart, ControllerDirection_LineEnd, DrawScale, FColor::Green, false, 0.0f, 0, Thickness);
}

// Called to bind functionality to input
void AARCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AARCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AARCharacter::MoveRight);
	
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AARCharacter::Jump);


	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &::AARCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("SecondaryAttack", IE_Pressed, this, &::AARCharacter::SecondaryAttack);
	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &::AARCharacter::PrimaryInteract);
}

