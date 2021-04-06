// Fill out your copyright notice in the Description page of Project Settings.


#include "Hack_SlashCharacterBase.h"

// Sets default values
AHack_SlashCharacterBase::AHack_SlashCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	InitMaxHealth();
	Health = MaxHealth;
}

// Called when the game starts or when spawned
void AHack_SlashCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHack_SlashCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AHack_SlashCharacterBase::OnAttackRequest()
{
	if (bCanAttack)
	{
		bCanAttack = false;
		bCanMove = false;
		bStartAttack = true;
		GetWorldTimerManager().SetTimer(CDTimer, this, &AHack_SlashCharacterBase::OnAttackCooledDown, AttackCoolDown, false);
	}
}

void AHack_SlashCharacterBase::OnAttackCooledDown()
{
	bCanAttack = true;
}
