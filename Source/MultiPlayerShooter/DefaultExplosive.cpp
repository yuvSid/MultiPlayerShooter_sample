// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultExplosive.h"

#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"

// Sets default values
ADefaultExplosive::ADefaultExplosive()
{
	bReplicates = true;
	Damage = 100.f;
	DamageRadius = 1000.f;
	bDamageNotScaled = true;

}

// Called when the game starts or when spawned
void ADefaultExplosive::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADefaultExplosive::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ADefaultExplosive::TakeDamage( float DamageTaken, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser )
{
	UGameplayStatics::ApplyRadialDamage( this, Damage, GetActorLocation(), DamageRadius, UDamageType::StaticClass(), TArray< AActor* >(), this, EventInstigator, bDamageNotScaled ); //TODO change constants for UPROPERTY
	Destroy();
	
	return 0.f;
}

