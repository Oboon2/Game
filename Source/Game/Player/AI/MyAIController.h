// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Player/MyCharacter.h"
#include "MyAIController.generated.h"

/**
 * 
 */
UCLASS()
class GAME_API AMyAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AMyAIController();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	class UBehaviorTreeComponent* BTComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
		class UBlackboardComponent* BBComponent;

	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

	void SetCurrentState(EMyState NewState);

	void SetTargetEnemy(AActor* Player);
};
