// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Enemy/Creep/CreepMonster.h"
#include "CreepAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class GAME_API UCreepAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		EMonsterState CurrentState = EMonsterState::Normal;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float Speed;
	
};
