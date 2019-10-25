// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "RTSUserWidget.h"
#include "Player/MyCharacter.h"
#include "Enemy/Creep/CreepMonster.h"
#include "Kismet/GameplayStatics.h"
#include "RTSCameraPawn.h"
#include "Enemy/Creep/AI/CreepAIController.h"


ARTSPlayerController::ARTSPlayerController()
{
	bShowMouseCursor = true;

	DefaultMouseCursor = EMouseCursor::Hand;

	//IsLocalPlayerController() - 본인꺼 찾아서 본인꺼만 제어할때 사용

	PrimaryActorTick.bCanEverTick = true;
}



void ARTSPlayerController::BeginPlay()
{
	Super::BeginPlay();
	HUDptr = Cast<ARTSHUD>(GetHUD());

	if (IsLocalPlayerController())
	{
		//FSoftClassPath RTSWidgetClass_CPP_PATH(TEXT("WidgetBlueprint'/Game/UI/BP_RTSUserWidget.BP_RTSUserWidget_C'"));

		//// #include "" 실행
		//UClass* RTSWidgetClass_BP = RTSWidgetClass_CPP_PATH.TryLoadClass<URTSUserWidget>();
		//if(RTSWidgetClass_BP)
		//{
		//	UE_LOG(LogClass, Warning, TEXT("111"));
		//}
		RTSWidget = CreateWidget<URTSUserWidget>(this, RTSWidgetClass);
		if (RTSWidget)
		{
			RTSWidget->AddToViewport();
		}
	}


}

void ARTSPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ARTSCameraPawn* SelectedPlayer = Cast<ARTSCameraPawn>(GetPawn());

	TArray<AActor*> Creeps;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACreepMonster::StaticClass(), Creeps);


	//UE_LOG(LogClass, Warning, TEXT("000"));

	ACreepMonster* Creep = Cast<ACreepMonster>(Creeps[0]);
	if (SelectedPlayer && Creep)
	{
		//UE_LOG(LogClass, Warning, TEXT("111"));
		if (bCheckRange == true)
		{
			//UE_LOG(LogClass, Warning, TEXT("222"));
			float Distance = FVector::Distance(SelectedPlayer->GetActorLocation(), Creep->GetActorLocation());
			if (Distance < 600)
			{
				
				bIsMove = true;
				if (bIsMove == true)
				{
					//UE_LOG(LogClass, Warning, TEXT("333"));
					UAIBlueprintHelperLibrary::SimpleMoveToLocation(SelectedPlayer->GetController(), Creep->GetActorLocation());
					bIsMove = false;
				}
			}
			else if (Distance < 150)
			{
				
				bCheckRange = false;
			}
			else
			{
				MoveReleased();
			}
		}
	}


}

void ARTSPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("LeftMouseClick", IE_Pressed, this, &ARTSPlayerController::SelectionPressed);

	InputComponent->BindAction("LeftMouseClick", IE_Released, this, &ARTSPlayerController::SelectionReleased);

	InputComponent->BindAction("RightMouseClick", IE_Pressed, this, &ARTSPlayerController::MoveReleased);

	InputComponent->BindAction("A", IE_Pressed, this, &ARTSPlayerController::AttackPressed);

	InputComponent->BindAction("A", IE_Released, this, &ARTSPlayerController::AttactReleased);
}

void ARTSPlayerController::SelectionPressed()
{
	if (HUDptr != nullptr)
	{
		if (bCheckAttack == true)
		{
			bCheckRange = true;
			//MoveReleased();
		}
		else
		{
			HUDptr->InitialPoint = HUDptr->GetMousePos2D();
			HUDptr->bStartSelecting = true;
		}

	}
}

void ARTSPlayerController::SelectionReleased()
{
	HUDptr->bStartSelecting = false;
	SelectedActors = HUDptr->FoundActors;
	if (bCheckAttack == true)
	{
		bCheckAttack = false;
		CurrentMouseCursor = EMouseCursor::Hand;
	}
}

void ARTSPlayerController::MoveReleased()
{
	if (SelectedActors.Num() > 0)
	{
		for (int32 i = 0; i < SelectedActors.Num(); ++i)
		{
			FHitResult Hit;
			GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, Hit);
			FVector MoveLocation = Hit.Location + FVector(i / 2 * 100, i % 2 * 100, 0);
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(SelectedActors[i]->GetController(), MoveLocation);
			DrawDebugSphere(GetWorld(), MoveLocation, 25, 10, FColor::Green, false, 0.5f);
		}
	}
}

void ARTSPlayerController::AttackPressed()
{
	if (SelectedActors.Num() > 0)
	{
		bIsAttack = true;
		bCheckAttack = true;
		CurrentMouseCursor = EMouseCursor::Crosshairs;
	}
}

void ARTSPlayerController::AttactReleased()
{
}

bool ARTSPlayerController::GetbIsAttack()
{
	return bIsAttack;
}
