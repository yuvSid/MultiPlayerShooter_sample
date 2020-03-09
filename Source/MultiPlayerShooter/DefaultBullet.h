// Fill out your copyright notice in the Description page of Project Settings.
// TODO change projectiles to rayCast bullet

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "DefaultBullet.generated.h"

UCLASS()
class MULTIPLAYERSHOOTER_API ADefaultBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADefaultBullet();

protected:
	UFUNCTION( Category = "Projectile" )
	void OnBulletImpact( UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit );

	//The damage type and damage that will be done by this bullet.
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Damage" )
	TSubclassOf<class UDamageType> DamageType;

	//The damage dealt by this bullet.
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Damage" )
	float Damage;

	// Sphere collision component.
	UPROPERTY( VisibleDefaultsOnly, Category = Projectile )
	class USphereComponent* CollisionComponent;

	// Bullet movement component.
	UPROPERTY( VisibleAnywhere, Category = Movement )
	class UProjectileMovementComponent* ProjectileMovementComponent;

public:	
	// Function that initializes the bullet's velocity in the shoot direction.
	UFUNCTION( NetMulticast, unreliable )
	void FireInDirection( const FVector& ShootDirection );


};
