// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

#include "DefaultBullet.generated.h"

UCLASS()
class MULTIPLAYERSHOOTER_API ADefaultBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADefaultBullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Sphere collision component.
	UPROPERTY( VisibleDefaultsOnly, Category = Projectile )
	USphereComponent* CollisionComponent;

	// Bullet movement component.
	UPROPERTY( VisibleAnywhere, Category = Movement )
	UProjectileMovementComponent* ProjectileMovementComponent;

	// Function that initializes the bullet's velocity in the shoot direction.
	UFUNCTION()
	void FireInDirection( const FVector& ShootDirection );

	// Function that is called when the projectile hits something.
	UFUNCTION()
	void OnHit( UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit );
};
