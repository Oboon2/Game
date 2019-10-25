// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Enemy/Creep/CreepMonster.h"
#include "CreepAIController.generated.h"

/**
 * 
 */
UCLASS()
class GAME_API ACreepAIController : public AAIController
{
	GENERATED_BODY()
public:
	ACreepAIController();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
		class UBehaviorTreeComponent* BTComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
		class UBlackboardComponent* BBComponent;

	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

	void SetCurrentState(EMonsterState NewState);

	void SetTargetPlayer(AActor* Player);

	
};
