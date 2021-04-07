// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Hack_SlashCharacterBase.h"
#include "AIController.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class HACK_SLASH_API AEnemyCharacter : public AHack_SlashCharacterBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual bool IsDead_Implementation() override {
		bool bDead = Super::IsDead_Implementation();
		AAIController* AIController = GetController<AAIController>();
		if (AIController && bDead) AIController->UnPossess();
		return bDead;
	};



private:

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
