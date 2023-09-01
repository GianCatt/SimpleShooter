// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

class AWeaponBase;
class AGun;
class ALauncher;

UCLASS()
class SIMPLESHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Weapons")
	TArray<TSubclassOf<AWeaponBase>> DefaultWeapons;
	
public:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
	TArray<AWeaponBase*> Weapons;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
	AWeaponBase* CurrentWeapon;
	
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
	int32 CurrentIndex = 0;
	
	UFUNCTION(BlueprintPure)
	bool IsDead() const;

	UFUNCTION(BlueprintPure)
	float GetHealthPercent() const;

	UFUNCTION(BlueprintPure)
	int32 GetCurrentWeaponAmmo() const;

	UFUNCTION(BlueprintCallable)
	void EquipWeapon(int32 index);

	void Shoot();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	
private:
	void Move(float AxisValue);
	void Strafe(float AxisValue);
	void LookUpRate(float AxisValue);
	void NextWeapon();
	void LastWeapon();

	UPROPERTY(EditAnywhere)
	float RotationRate = 10.f;

	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 100.f;

	UPROPERTY(VisibleAnywhere)
	float Health;
	
	UPROPERTY()
	AWeaponBase* Gun;
	UPROPERTY()
	AWeaponBase* Launcher;
	
};
