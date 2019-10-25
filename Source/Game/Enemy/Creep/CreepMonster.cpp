// Fill out your copyright notice in the Description page of Project Settings.


#include "CreepMonster.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "Player/MyCharacter.h"
#include "Enemy/Creep/AI/CreepAIController.h"
#include "GameFramework/CharacterMovementComponent.h "
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "RTSCameraPawn.h"
#include "RTSPlayerController.h"

// Sets default values
ACreepMonster::ACreepMonster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -88.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	PawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensing"));
	PawnSensing->SightRadius = 400.0f;
	PawnSensing->SensingInterval = 0.1f;
	PawnSensing->SetPeripheralVisionAngle(90.0f);
	PawnSensing->bSeePawns = true;
	PawnSensing->bHearNoises = false;
	GetCharacterMovement()->MaxWalkSpeed = 150.0f;


	Tags.Add(TEXT("Creep"));
}

// Called when the game starts or when spawned
void ACreepMonster::BeginPlay()
{
	Super::BeginPlay();
	CurrentHP = MaxHP;

	PawnSensing->OnSeePawn.AddDynamic(this, &ACreepMonster::OnSeenPawn);
	PawnSensing->OnHearNoise.AddDynamic(this, &ACreepMonster::OnHeardNoise);
}

// Called every frame
void ACreepMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACreepMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ACreepMonster::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	if (CurrentHP == 0)
	{
		return 0;
	}
	if (DamageEvent.IsOfType(FRadialDamageEvent::ClassID))
	{
		FRadialDamageEvent* RadialDamageEvent = (FRadialDamageEvent*)(&DamageEvent);
		if (RadialDamageEvent)
		{
			UE_LOG(LogClass, Warning, TEXT("FRadialDamageEvent %f"), DamageAmount);
			CurrentHP -= DamageAmount;
		}
	}
	else if (DamageEvent.IsOfType(FPointDamageEvent::ClassID))
	{
		FPointDamageEvent* PointDamageEvent = (FPointDamageEvent*)(&DamageEvent);
		CurrentHP -= DamageAmount;
	}
	else
	{
		UE_LOG(LogClass, Warning, TEXT("FDamageEvevt %f"), DamageAmount);
		CurrentHP -= DamageAmount;
	}

	FString HitName = FString::Printf(TEXT("Hit%d"), FMath::RandRange(1, 2));

	PlayAnimMontage(HitAnimation, 2.0f, FName(*HitName));

	CurrentHP = FMath::Clamp<float>(CurrentHP, 0, MaxHP);

	if (CurrentHP == 0)
	{
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		//GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		//GetMesh()->SetSimulatePhysics(true);

		//FString DeadName = FString::Printf(TEXT("Death_%d"), FMath::RandRange(1, 3));
		//PlayAnimMontage(DeadAnimation, 1.0f, FName(*DeadName));
		CurrentState = EMonsterState::Dead;
		ACreepAIController* AIC = Cast<ACreepAIController>(GetController());
		if (AIC)
		{
			AIC->SetCurrentState(CurrentState);
		}
	}

	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void ACreepMonster::OnSeenPawn(APawn * Pawn)
{
	AMyCharacter* Player = Cast<AMyCharacter>(Pawn);
	//UE_LOG(LogClass, Warning, TEXT("Seen1"));
	//ARTSCameraPawn* Player = Cast<ARTSCameraPawn>(GetController());
	UE_LOG(LogClass, Warning, TEXT("Seen %s"),*Pawn->GetName());
	if (!Player)
	{
		UE_LOG(LogClass, Warning, TEXT("player "));
		return;
	}

	if (CurrentState == EMonsterState::Normal && Player->ActorHasTag(TEXT("Player")) && Player->CurrentHP > 0)
	{
		UE_LOG(LogClass, Warning, TEXT("Seen2 %s"), *Pawn->GetName());
		CurrentState = EMonsterState::Chase;
		ACreepAIController* AIC = Cast<ACreepAIController>(GetController());
		if (AIC)
		{
			 AIC->SetCurrentState(CurrentState);
			 AIC->SetTargetPlayer(Player);
		}
	}
	//UE_LOG(LogClass, Warning, TEXT("Seen %s"), *Pawn->GetName());
}

void ACreepMonster::OnHeardNoise(APawn * Pawn, const FVector & Location, float Volume)
{
}

void ACreepMonster::Attack()
{
	ACreepAIController* AIC = Cast<ACreepAIController>(GetController());
	if (AIC)
	{
		AActor* Player = Cast<AActor>(AIC->BBComponent->GetValueAsObject(FName(TEXT("Player"))));
		if (Player)
		{
			UGameplayStatics::ApplyDamage(Player, 30.0f, GetController(), this, nullptr);
		}
	}
}

