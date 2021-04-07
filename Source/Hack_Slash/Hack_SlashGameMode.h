// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Hack_SlashGameMode.generated.h"

UCLASS(minimalapi)
class AHack_SlashGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AHack_SlashGameMode();
protected:
	virtual void BeginPlay() override;
private:
	UPROPERTY(EditDefaultsOnly)
		float HealthSpawnCD = 10;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class AHealthPack> HealthPackClass;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class AEnemyCharacter> ZombieClass;
	UPROPERTY(EditDefaultsOnly)
		TArray<int> Waves;
	UPROPERTY(EditDefaultsOnly)
		int InitialBeforeWaveCd = 10;

	TArray<class AVolume*> HealthSpawners;
	TArray<class AVolume*> ZombieSpawners;
	FTimerHandle HealthPackSpawnTimer;
	FTimerHandle BeforeWaveTimer;
	void OnSpawnHealthPack();
	void OnCountDown();
	void NextWave();
	void SpawnWave();
public:
	UPROPERTY(BlueprintReadOnly)
		int CurrentWave = 0;
	UPROPERTY(BlueprintReadOnly)
		int RemainingZombies = 1;
	UPROPERTY(BlueprintReadOnly)
		int BeforeWaveTime = 10;
	UPROPERTY(BlueprintReadOnly)
		bool bShowRemainingTime = false;
	UPROPERTY(BlueprintReadOnly)
		bool bShowRemainingZombies = false;
	UFUNCTION(BlueprintNativeEvent)
		void OnGameWin();
	void OnGameWin_Implementation() { UGameplayStatics::SetGamePaused(GetWorld(), true); };
	UFUNCTION(BlueprintNativeEvent)
		void OnGameLose();
	void OnGameLose_Implementation() { UGameplayStatics::SetGamePaused(GetWorld(), true); };
	void OnZombieDeath();
};



