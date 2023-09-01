// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "Gun.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AGun : public AWeaponBase
{
	GENERATED_BODY()

public:
	AGun();

	virtual void PullTrigger() override;

protected:
	// Called when the game starts or when spawned
	void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	float MaxRange = 1000.f;

	UPROPERTY(EditAnywhere)
	float Damage = 20.f;

	bool GunTrace(FHitResult& Hit, FVector& ShotDirection);
	AController* GetOwnerController() const;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
