// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"
#include "MyCharacter.h"
#include "Gameframework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/InputComponent.h"
#include "RTSPlayerController.h"

void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	AMyCharacter* Pawn = Cast<AMyCharacter>(TryGetPawnOwner());
	if (Pawn)
	{
		ARTSPlayerController* PC = Cast<ARTSPlayerController>(Pawn->GetController());
		if (PC)
		{
			bIsAttack = PC->GetbIsAttack();
		}
	}

	if (Pawn && Pawn->IsValidLowLevel())
	{
		Speed = Pawn->GetCharacterMovement()->Velocity.Size();
	}
}
