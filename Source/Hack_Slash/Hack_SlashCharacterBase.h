// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Damageable.h"
#include "Hack_SlashCharacterBase.generated.h"

UCLASS()
class HACK_SLASH_API AHack_SlashCharacterBase : public ACharacter, public IDamageable
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHack_SlashCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void OnAttackRequest();
	void OnAttackCooledDown();
	float GetDamage() { return Damage; }
	UPROPERTY(Blueprintreadwrite)
		bool bStartAttack = false;
	UPROPERTY(Blueprintreadwrite)
		bool bAttacking = false;
	UPROPERTY(Blueprintreadwrite)
		bool bCanMove = true;
	UPROPERTY(Blueprintreadonly)
		bool bCanAttack = true;
	// Inherited via IDamageable

	virtual float GetMaxHealth_Implementation() override { return MaxHealth; };

	virtual float GetHealth_Implementation() override { return Health; };

	virtual void InitMaxHealth() override { MaxHealth = InitialMaxHealth; };

	virtual bool IsDead_Implementation() override {
		if(bDead) bCanMove = false;
		return bDead;
	};
private:
	UPROPERTY(EditDefaultsOnly)
		float InitialMaxHealth = 100;

	UPROPERTY(EditDefaultsOnly)
		float AttackCoolDown = 5.0f;

	UPROPERTY(EditDefaultsOnly)
		float Damage = 20;

	FTimerHandle CDTimer;



};
