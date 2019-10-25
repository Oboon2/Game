// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"
#include "RTSHUD.h"
#include "RTSPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GAME_API ARTSPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	ARTSPlayerController();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupInputComponent() override;

	ARTSHUD* HUDptr;

	UFUNCTION()
	void SelectionPressed();

	UFUNCTION()
	void SelectionReleased();

	UFUNCTION()
	void MoveReleased();

	UFUNCTION()
	void AttackPressed();

	UFUNCTION()
	void AttactReleased();

	UFUNCTION()
	bool GetbIsAttack();

	UPROPERTY()
	TArray <AMyCharacter*> SelectedActors;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<class URTSUserWidget> RTSWidgetClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	class URTSUserWidget* RTSWidget;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	bool bIsAttack = false;


	bool bCheckAttack = false;
	bool bCheckRange = false;
	bool bIsMove = false;

};
