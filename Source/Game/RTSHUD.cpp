// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSHUD.h"
#include "Player/MyCharacter.h"

void ARTSHUD::DrawHUD()
{
	if (bStartSelecting == true)
	{
		if (FoundActors.Num() > 0)
		{
			for (int32 i = 0;
				i < FoundActors.Num(); ++i)
			{
				FoundActors[i]->SetDeSelected();
			}
		}
		FoundActors.Empty();

		CurrentPoint = GetMousePos2D();
		DrawRect(FLinearColor(0.0f, 1.0f, 0.0f, 0.15f), InitialPoint.X, InitialPoint.Y, CurrentPoint.X - InitialPoint.X, CurrentPoint.Y - InitialPoint.Y);

		GetActorsInSelectionRectangle<AMyCharacter>(InitialPoint, CurrentPoint, FoundActors, false, false);

		if (FoundActors.Num() > 0)
		{
			for (int32 i = 0; i < FoundActors.Num(); ++i)
			{
				FoundActors[i]->SetSelected();
			}
		}
	}
}

FVector2D ARTSHUD::GetMousePos2D()
{
	float PosX;
	float PosY;
	GetOwningPlayerController()->GetMousePosition(PosX, PosY);

	return FVector2D(PosX, PosY);
}
