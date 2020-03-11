// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DefaultExplosive.generated.h"

UCLASS()
class MULTIPLAYERSHOOTER_API ADefaultExplosive : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADefaultExplosive();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Damage" )
	float Damage;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Damage" )
	float DamageRadius;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Damage" )
	uint8 bDamageNotScaled:1;
	   
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	float TakeDamage( float DamageTaken, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser ) override;

};
