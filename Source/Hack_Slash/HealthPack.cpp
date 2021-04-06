// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPack.h"
#include "Components/SphereComponent.h"

// Sets default values
AHealthPack::AHealthPack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionSphere = CreateDefaultSubobject<USphereComponent>("CollisionSphere");
	CollisionSphere->SetGenerateOverlapEvents(true);
	RootComponent = CollisionSphere;
	CollisionSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
}

// Called when the game starts or when spawned
void AHealthPack::BeginPlay()
{
	Super::BeginPlay();
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AHealthPack::OnOverlapBegin);
}

// Called every frame
void AHealthPack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHealthPack::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Destroy();
}

