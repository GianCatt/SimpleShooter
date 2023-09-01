// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

UCLASS()
class SIMPLESHOOTER_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UParticleSystem* MuzzleFlash;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UParticleSystem* BulletHole;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	USoundBase* MuzzleSound;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	USoundBase* ImpactSound;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
