// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RTSUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAME_API URTSUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		class UImage* TopUI;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		class UImage* BottomUI;
};
