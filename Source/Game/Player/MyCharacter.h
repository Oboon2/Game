// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

UENUM(BlueprintType)
enum class EMyState : uint8
{
	None = 0 UMETA(DisplayName = "None"),
	Normal = 1 UMETA(DisplayName = "Normal"),
	Chase = 2 UMETA(DisplayName = "Chase"),
	Battle = 3 UMETA(DisplayName = "Battle"),
	Dead = 4 UMETA(DisplayName = "Dead"),
};

UCLASS()
class GAME_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SetSelected();

	void SetDeSelected();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UBehaviorTree* PlayerAI;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UPawnSensingComponent* PawnSensing;

	UFUNCTION()
	void OnSeenPawn(APawn* Pawn);
private:

	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere)
	class UDecalComponent* CursorToWorld;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float CurrentHP = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float MaxHP = 100.0f;

	float HealthPoint;
	float ManaPoint;
	float Armor;
	float Str;
	float Agi;
	float Int;



};
