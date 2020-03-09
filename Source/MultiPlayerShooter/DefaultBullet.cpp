// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultBullet.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "Components/StaticMeshComponent.h"
#include "GameFramework/DamageType.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
//#include "UObject/ConstructorHelpers.h"

// Sets default values
ADefaultBullet::ADefaultBullet()
{
	bReplicates = true;
	
	// Use a sphere as a simple collision representation.
	CollisionComponent = CreateDefaultSubobject<USphereComponent>( TEXT( "RootComponent" ) );
	CollisionComponent->InitSphereRadius( 15.0f ); //TODO add connection with blueprint scale
	CollisionComponent->SetCollisionProfileName( TEXT( "BlockAllDynamic" ) );
	RootComponent = CollisionComponent;

	//Registering the Projectile Impact function on a Hit event.
	if ( Role == ROLE_Authority )
		CollisionComponent->OnComponentHit.AddDynamic( this, &ADefaultBullet::OnBulletImpact );
	
	// Use this component to drive this bullet's movement.
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>( TEXT( "ProjectileMovementComponent" ) );
	ProjectileMovementComponent->SetUpdatedComponent( CollisionComponent );
	ProjectileMovementComponent->InitialSpeed = 3000.0f;
	ProjectileMovementComponent->MaxSpeed = 3000.0f; //TODO chnage for settable in editor parametrs 
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->ProjectileGravityScale = 0.01f;

	// Die after 3 seconds.
	InitialLifeSpan = 3.0f;

	DamageType = UDamageType::StaticClass();
	Damage = 40.0f;
}

void ADefaultBullet::OnBulletImpact( UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit )
{
	if ( OtherActor )
	{
		UGameplayStatics::ApplyPointDamage( OtherActor, Damage, NormalImpulse, Hit, Instigator->Controller, this, DamageType );
	}

	Destroy();
}

// Function that initializes the projectile's velocity in the shoot direction.
void ADefaultBullet::FireInDirection_Implementation( const FVector& ShootDirection )
{
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}


