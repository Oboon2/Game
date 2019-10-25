// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSCameraPawn.h"
#include "Components/SceneComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"

// Sets default values
ARTSCameraPawn::ARTSCameraPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootComponent = RootScene;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootScene);
	SpringArm->bDoCollisionTest = false;
	SpringArm->SetRelativeRotation(FRotator(-70.0f, 0.0f, 0.0f));
	SpringArm->TargetArmLength = DefaultZoom;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

}

// Called when the game starts or when spawned
void ARTSCameraPawn::BeginPlay()
{
	Super::BeginPlay();
	
	PC = Cast<APlayerController>(GetController());
	PC->GetViewportSize(ScreenSizeX, ScreenSizeY);
}

// Called every frame
void ARTSCameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CamDir = GetCameraPanDirection() * CameraSpeed;
	PanMoveCamera(CamDir);


}

// Called to bind functionality to input
void ARTSCameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("ZoomIn"), IE_Pressed, this, &ARTSCameraPawn::ZoomIn);
	PlayerInputComponent->BindAction(TEXT("ZoomOut"), IE_Released, this, &ARTSCameraPawn::ZoomOut);
	PlayerInputComponent->BindAction(TEXT("ZoomReset"), IE_Released, this, &ARTSCameraPawn::ZoomReset);
}

FVector ARTSCameraPawn::GetCameraPanDirection()
{
	float MousePosX;
	float MousePosY;
	float CameraDirectionX = 0;
	float CameraDirectionY = 0;

	PC->GetMousePosition(MousePosX, MousePosY);
	
	if (MousePosX <= Margin)
	{
		CameraDirectionY = -1;
	}

	if (MousePosY <= Margin)
	{
		CameraDirectionX = 1;
	}

	if (MousePosX >= ScreenSizeX - Margin)
	{
		CameraDirectionY = 1;
	}

	if (MousePosY >= ScreenSizeY - Margin)
	{
		CameraDirectionX = -1;
	}


	return FVector(CameraDirectionX, CameraDirectionY, 0);
}

void ARTSCameraPawn::PanMoveCamera(FVector & PanDirection)
{
	if (PanDirection == FVector::ZeroVector)
	{
		return;
	}
	else
	{
		AddActorLocalOffset(GetCameraPanDirection() * CameraSpeed);
	}
}

void ARTSCameraPawn::ZoomIn()
{
	if ((SpringArm->TargetArmLength - ZoomSpeed) <= MinZoomLimit)
	{
		SpringArm->TargetArmLength = MinZoomLimit;
	}
	else
	{
		SpringArm->TargetArmLength = SpringArm->TargetArmLength - ZoomSpeed;
	}
}

void ARTSCameraPawn::ZoomOut()
{
	if ((SpringArm->TargetArmLength + ZoomSpeed) >= MaxZoomLimit)
	{
		SpringArm->TargetArmLength = MaxZoomLimit;
	}
	else
	{
		SpringArm->TargetArmLength = SpringArm->TargetArmLength + ZoomSpeed;
	}
}

void ARTSCameraPawn::ZoomReset()
{
	SpringArm->TargetArmLength = DefaultZoom;
}

