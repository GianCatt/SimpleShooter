// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Launcher.generated.h"

UCLASS()
class SIMPLESHOOTER_API ALauncher : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALauncher();

	void SpawnProjectile();

	UFUNCTION(BlueprintPure, Category = "Ammo")
	int32 GetRemainingAmmo() const { return AmmoCount; }

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditAnywhere)
	UParticleSystem* MuzzleFlash;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AProjectile> ProjectileClass;

	AController* GetOwnerController() const;

	FString GunName = "XM-25 Grenade Launcher";

	UPROPERTY(EditAnywhere)
	int32 AmmoCount = 7;

	UPROPERTY(EditAnywhere)
	float Offset = 150.f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	

};
