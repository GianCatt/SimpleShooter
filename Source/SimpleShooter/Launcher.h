// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "GameFramework/Actor.h"
#include "Launcher.generated.h"

UCLASS()
class SIMPLESHOOTER_API ALauncher : public AWeaponBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALauncher();

	virtual void PullTrigger() override;

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AProjectile> ProjectileClass;

	AController* GetOwnerController() const;
	
	UPROPERTY(EditAnywhere)
	float SpawnOffset = 150.f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	

};
