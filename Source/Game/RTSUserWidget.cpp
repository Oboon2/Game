// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSUserWidget.h"
#include "Components/Image.h"
#include "GameGameModeBase.h"
#include "RTSPlayerController.h"

void URTSUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	TopUI = Cast<UImage>(GetWidgetFromName(TEXT("TopUI")));
	BottomUI = Cast<UImage>(GetWidgetFromName(TEXT("BottomUI")));
}
