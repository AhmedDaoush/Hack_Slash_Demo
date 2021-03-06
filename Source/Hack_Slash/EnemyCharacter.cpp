// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Hack_SlashCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Hack_SlashGameMode.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	InitMaxHealth();
	Health = MaxHealth;
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AEnemyCharacter::OnOverlapBegin);
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyCharacter::OnDead()
{
	AHack_SlashGameMode* gamemode = Cast<AHack_SlashGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	gamemode->OnZombieDeath();
}

void AEnemyCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AHack_SlashCharacterBase* character = Cast<AHack_SlashCharacterBase>(OtherActor);
	if (character && character->bAttacking)
	{
		if (OtherComp->ComponentHasTag("Weapon"))
		{
			ChangeHealth(-character->GetDamage());
		}
	}
	
}









