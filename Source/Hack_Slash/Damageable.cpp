// Fill out your copyright notice in the Description page of Project Settings.


#include "Damageable.h"

// Add default functionality here for any IDamageable functions that are not pure virtual.

void IDamageable::ChangeHealth(float delta)
{
	Health += delta;
	if (Health > MaxHealth)
		Health = MaxHealth;
	else if (Health < 0)
		Health = 0;
}
