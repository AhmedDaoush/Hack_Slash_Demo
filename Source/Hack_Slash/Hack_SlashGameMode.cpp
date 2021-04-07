// Copyright Epic Games, Inc. All Rights Reserved.

#include "Hack_SlashGameMode.h"
#include "Hack_SlashPlayerController.h"
#include "EnemyCharacter.h"
#include "Hack_SlashCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"
#include "GameFramework/Volume.h"
#include "HealthPack.h"

AHack_SlashGameMode::AHack_SlashGameMode()
{


	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Hack_Slash/BluePrints/Hero"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AHack_SlashGameMode::BeginPlay()
{
	Super::BeginPlay();
	if (HealthPackClass)
	{
		TArray<AActor*> OutActors;
		UGameplayStatics::GetAllActorsWithTag(GetWorld(), "HealthSpawner", OutActors);
		for (AActor* actor : OutActors)
		{
			AVolume* SpawnerVolume = Cast<AVolume>(actor);
			if (SpawnerVolume)
			{
				HealthSpawners.Add(SpawnerVolume);
			}
		}
		if (HealthSpawners.Num())
		{
			GetWorldTimerManager().SetTimer(HealthPackSpawnTimer, this, &AHack_SlashGameMode::OnSpawnHealthPack, HealthSpawnCD, true);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("No Health Pack Spawners Found"));
		}
	}
	if (ZombieClass)
	{
		TArray<AActor*> OutActors;
		UGameplayStatics::GetAllActorsWithTag(GetWorld(), "ZombieSpawner", OutActors);
		for (AActor* actor : OutActors)
		{
			AVolume* SpawnerVolume = Cast<AVolume>(actor);
			if (SpawnerVolume)
			{
				ZombieSpawners.Add(SpawnerVolume);
			}
		}
		NextWave();
	}
}

void AHack_SlashGameMode::OnSpawnHealthPack()
{
	int32 SpawnerIdx = FMath::RandRange(0, HealthSpawners.Num() - 1);
	FVector SpawnLocation = FMath::RandPointInBox(HealthSpawners[SpawnerIdx]->GetBounds().GetBox());
	GetWorld()->SpawnActor<AHealthPack>(HealthPackClass, SpawnLocation, FRotator::ZeroRotator);
}

void AHack_SlashGameMode::OnCountDown()
{
	--BeforeWaveTime;
	if (BeforeWaveTime <= 0)
	{
		bShowRemainingTime = false;
		bShowRemainingZombies = true;
		SpawnWave();
		GetWorldTimerManager().ClearTimer(BeforeWaveTimer);
	}

}

void AHack_SlashGameMode::NextWave()
{
	++CurrentWave;
	if (CurrentWave > Waves.Num())
		OnGameWin();
	else
	{
		bShowRemainingTime = true;
		bShowRemainingZombies = false;
		BeforeWaveTime = InitialBeforeWaveCd;
		GetWorldTimerManager().SetTimer(BeforeWaveTimer, this, &AHack_SlashGameMode::OnCountDown, 1, true);
	}
}

void AHack_SlashGameMode::SpawnWave()
{
	for (int i = 0; i < Waves[CurrentWave-1]; i++)
	{
		int32 SpawnerIdx = FMath::RandRange(0, ZombieSpawners.Num() - 1);
		FVector SpawnLocation = FMath::RandPointInBox(ZombieSpawners[SpawnerIdx]->GetBounds().GetBox());
		GetWorld()->SpawnActor<AEnemyCharacter>(ZombieClass, SpawnLocation, FRotator::ZeroRotator);
	}
	RemainingZombies = Waves[CurrentWave - 1];
}

void AHack_SlashGameMode::OnZombieDeath()
{
	--RemainingZombies;
	if (RemainingZombies <= 0)
		NextWave();
}
