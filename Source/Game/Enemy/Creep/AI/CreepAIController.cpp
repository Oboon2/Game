// Fill out your copyright notice in the Description page of Project Settings.


#include "CreepAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/Creep/CreepMonster.h"
#include "BehaviorTree/BehaviorTree.h"
#include "RTSPlayerController.h"

ACreepAIController::ACreepAIController()
{
	BTComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BTComponent"));
	BBComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BBComponent"));
}


void ACreepAIController::OnPossess(APawn * InPawn)
{
	Super::OnPossess(InPawn);

	ACreepMonster* Creep = Cast<ACreepMonster>(InPawn);
	if (Creep && BTComponent && BBComponent)
	{
		UE_LOG(LogClass, Warning, TEXT("%d"), Creep->CreepAI->BlackboardAsset);

		BBComponent->InitializeBlackboard(*(Creep->CreepAI->BlackboardAsset));
		BTComponent->StartTree(*(Creep->CreepAI));

		//Creep->GetActorLocation()
		//BBComponent->SetValueAsVector(FName(TEXT("Target")), FVector(100.0f, 100.0f, 0.0f));
		SetCurrentState(EMonsterState::Normal);
	}
}

void ACreepAIController::OnUnPossess()
{
	BTComponent->StopTree();

	Super::OnUnPossess();
}

void ACreepAIController::SetCurrentState(EMonsterState NewState)
{
	BBComponent->SetValueAsEnum(FName(TEXT("CurrentState")), (uint8)NewState);
}

void ACreepAIController::SetTargetPlayer(AActor* Player)
{
	BBComponent->SetValueAsObject(FName(TEXT("Player")), Player);
}


