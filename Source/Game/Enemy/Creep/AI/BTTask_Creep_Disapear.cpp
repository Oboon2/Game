// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Creep_Disapear.h"
#include "Enemy/Creep/AI/CreepAIController.h"

EBTNodeResult::Type UBTTask_Creep_Disapear::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	ACreepAIController* AIC = Cast<ACreepAIController>(OwnerComp.GetOwner());

	if (AIC)
	{
		AIC->GetPawn()->Destroy();
	}
	return EBTNodeResult::Succeeded;
}
