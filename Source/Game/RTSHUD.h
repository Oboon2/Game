// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Player/MyCharacter.h"
#include "RTSHUD.generated.h"

/**
 * 
 */
UCLASS()
class GAME_API ARTSHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	virtual void DrawHUD() override;

	FVector2D InitialPoint;

	FVector2D CurrentPoint;

	FVector2D GetMousePos2D();

	UPROPERTY()
	bool bStartSelecting;

	UPROPERTY()
	TArray <AMyCharacter*> FoundActors;
};
