// Fill out your copyright notice in the Description page of Project Settings.


#include "AIShooterController.h"

#include "ShooterCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void AAIShooterController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}


void AAIShooterController::BeginPlay()
{
	Super::BeginPlay();

	FVector StartLocation = GetPawn()->GetActorLocation();

	if (AIBehavior != nullptr)
	{
		RunBehaviorTree(AIBehavior);

		APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		
		GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
	}
}

bool AAIShooterController::isDead() const
{
	AShooterCharacter* ControlledCharacter = Cast<AShooterCharacter>(GetPawn());
	if (ControlledCharacter != nullptr)
	{
		return ControlledCharacter->IsDead();
	}

	return true;
}



