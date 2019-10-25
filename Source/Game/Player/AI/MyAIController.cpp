// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Player/MyCharacter.h"
#include "BehaviorTree/BehaviorTree.h"

AMyAIController::AMyAIController()
{
	BTComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BTComponent"));
	BBComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BBComponent"));
}

void AMyAIController::OnPossess(APawn * InPawn)
{
	Super::OnPossess(InPawn);

	AMyCharacter* Player = Cast<AMyCharacter>(InPawn);
	if (Player && BTComponent && BBComponent)
	{

		BBComponent->InitializeBlackboard(*(Player->PlayerAI->BlackboardAsset));
		BTComponent->StartTree(*(Player->PlayerAI));


		//BBComponent->SetValueAsVector(FName(TEXT("Target")), FVector(100.0f, 100.0f, 0.0f));
		SetCurrentState(EMyState::Normal);
	}
}

void AMyAIController::OnUnPossess()
{
	BTComponent->StopTree();

	Super::OnUnPossess();
}

void AMyAIController::SetCurrentState(EMyState NewState)
{
	BBComponent->SetValueAsEnum(FName(TEXT("CurrentState")), (uint8)NewState);
}

void AMyAIController::SetTargetEnemy(AActor * Player)
{
	BBComponent->SetValueAsObject(FName(TEXT("Player")), Player);
}
