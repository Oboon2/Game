// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "RTSCameraPawn.generated.h"

UCLASS()
class GAME_API ARTSCameraPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ARTSCameraPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere)
	class USceneComponent* RootScene;

	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* Camera;

	UPROPERTY()
	APlayerController* PC;

	UFUNCTION()
	FVector GetCameraPanDirection();


	UPROPERTY()
	float Margin = 15.0f;

	UPROPERTY()
	int32 ScreenSizeX;

	UPROPERTY()
	int32 ScreenSizeY;

	UPROPERTY()
	float CameraSpeed = 20;

	UFUNCTION()
	void PanMoveCamera(FVector& PanDirection);
	
	void ZoomIn();

	void ZoomOut();

	void ZoomReset();

	UPROPERTY()
	float DefaultZoom = 1500.0f;

	UPROPERTY()
	float ZoomSpeed = 150.0f;

	UPROPERTY()
	float MinZoomLimit = 300.0f;
	UPROPERTY()

	float MaxZoomLimit = 3000.0f;


};
