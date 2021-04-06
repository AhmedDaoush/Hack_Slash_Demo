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

	void OnAttackRequest();
	void OnAttackCooledDown();

	UPROPERTY(Blueprintreadwrite)
		bool bStartAttack = false;
	UPROPERTY(Blueprintreadwrite)
		bool bAttacking = false;
	UPROPERTY(Blueprintreadwrite)
		bool bCanMove = true;

	// Inherited via IDamageable

	virtual float GetMaxHealth_Implementation() override { return MaxHealth; };

	virtual float GetHealth_Implementation() override { return Health; };

	virtual void InitMaxHealth() override { MaxHealth = InitialMaxHealth; };

private:
	UPROPERTY(EditDefaultsOnly)
		float InitialMaxHealth = 100;

	UPROPERTY(EditDefaultsOnly)
		float AttackCoolDown = 5.0f;

	bool bCanAttack = true;
	FTimerHandle CDTimer;



};
