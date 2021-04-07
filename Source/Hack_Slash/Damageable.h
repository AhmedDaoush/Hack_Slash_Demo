// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Damageable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UDamageable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class HACK_SLASH_API IDamageable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	float Health = 100.0f;
	float MaxHealth = 100.0f;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	float GetHealth();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	float GetMaxHealth();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool IsDead();

	virtual bool IsDead_Implementation(){
		return Health <= 0.01f;
	};

	virtual void ChangeHealth(float delta);
private:
	virtual void InitMaxHealth() = 0;
};
