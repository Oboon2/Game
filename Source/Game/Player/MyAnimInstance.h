// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class GAME_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	int a;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float Speed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bIsAttack = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bUseQ;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bUseW;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bUseE;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bUseR;


};
