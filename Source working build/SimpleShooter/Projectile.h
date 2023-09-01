// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class AShooterCharacter;
class URadialForceComponent;
class UProjectileMovementComponent;

UCLASS()
class SIMPLESHOOTER_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();
	UPROPERTY()
	FVector ExplosionLocation;
private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(VisibleAnywhere)
	URadialForceComponent* RadialForceComponent;
	
	UPROPERTY(EditDefaultsOnly)
	float Damage = 50.f;
	UPROPERTY(EditDefaultsOnly)
	float ExplosionRadius = 100.f;
	UPROPERTY(EditDefaultsOnly)
	float ExplosionForce = 100.f;
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent *HitComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit);

	AShooterCharacter* ShooterCharacter;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
