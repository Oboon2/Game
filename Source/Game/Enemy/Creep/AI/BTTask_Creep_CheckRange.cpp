// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Creep_CheckRange.h"

#include "Enemy/Creep/AI/CreepAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Player/MyCharacter.h"
#include "Enemy/Creep/CreepMonster.h"

EBTNodeResult::Type UBTTask_Creep_CheckRange::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	ACreepMonster* Creep = Cast<ACreepMonster>(OwnerComp.GetAIOwner()->GetPawn());
	AActor* Player = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey()));

	if (!Player && !Creep)
	{
		return EBTNodeResult::Failed;
	}
	if (Player)
	{
		float Distance = FVector::Distance(Creep->GetActorLocation(), Player->GetActorLocation());


		switch (Condition)
		{

		case ETaskCondition::Less:
		{
			if (Distance < Range)
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsEnum(FName(TEXT("CurrentState")), (uint8)TargetState);
				Creep->CurrentState = TargetState;
			}
			break;
		}

		case ETaskCondition::Greater:
		{
			if (Distance > Range)
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsEnum(FName(TEXT("CurrentState")), (uint8)TargetState);
				Creep->CurrentState = TargetState;
			}
			break;
		}

		}
	}

	return EBTNodeResult::Type();
}
