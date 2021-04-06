// Copyright Epic Games, Inc. All Rights Reserved.

#include "Hack_SlashGameMode.h"
#include "Hack_SlashPlayerController.h"
#include "Hack_SlashCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"
#include "GameFramework/Volume.h"
#include "HealthPack.h"

AHack_SlashGameMode::AHack_SlashGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AHack_SlashPlayerController::StaticClass();

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
}

void AHack_SlashGameMode::OnSpawnHealthPack()
{
	int32 SpawnerIdx = FMath::RandRange(0, HealthSpawners.Num() - 1);
	FVector SpawnLocation = FMath::RandPointInBox(HealthSpawners[SpawnerIdx]->GetBounds().GetBox());
	GetWorld()->SpawnActor<AHealthPack>(HealthPackClass, SpawnLocation, FRotator::ZeroRotator);
}
