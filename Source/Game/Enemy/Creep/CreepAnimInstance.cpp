// Fill out your copyright notice in the Description page of Project Settings.


#include "CreepAnimInstance.h"
#include "Enemy/Creep/CreepMonster.h"
#include "GameFramework/CharacterMovementComponent.h"

void UCreepAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	ACreepMonster* Pawn = Cast<ACreepMonster>(TryGetPawnOwner());
	if (Pawn && Pawn->IsValidLowLevel())
	{
		CurrentState = Pawn->CurrentState;
		Speed = Pawn->GetCharacterMovement()->Velocity.Size();
	}

}