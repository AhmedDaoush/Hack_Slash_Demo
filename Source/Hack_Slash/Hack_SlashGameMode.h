// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
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
	TArray<class AVolume*> HealthSpawners;
	FTimerHandle HealthPackSpawnTimer;
	void OnSpawnHealthPack();
};



