// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultBullet.h"

// Sets default values
ADefaultBullet::ADefaultBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Use a sphere as a simple collision representation.
	CollisionComponent = CreateDefaultSubobject<USphereComponent>( TEXT( "SphereComponent" ) );
	CollisionComponent->BodyInstance.SetCollisionProfileName( TEXT( "Projectile" ) );
	CollisionComponent->OnComponentHit.AddDynamic( this, &ADefaultBullet::OnHit );

	// Set the sphere's collision radius.
	CollisionComponent->InitSphereRadius( 15.0f );
	// Set the root component to be the collision component.
	RootComponent = CollisionComponent;

	// Use this component to drive this bullet's movement.
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>( TEXT( "ProjectileMovementComponent" ) );
	ProjectileMovementComponent->SetUpdatedComponent( CollisionComponent );
	ProjectileMovementComponent->InitialSpeed = 3000.0f;
	ProjectileMovementComponent->MaxSpeed = 3000.0f; //TODO chnage for settable in editor parametrs 
	ProjectileMovementComponent->bRotationFollowsVelocity = true;

	// Die after 3 seconds.
	InitialLifeSpan = 3.0f;
}

// Called when the game starts or when spawned
void ADefaultBullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADefaultBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Function that initializes the projectile's velocity in the shoot direction.
void ADefaultBullet::FireInDirection( const FVector& ShootDirection )
{
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}

//TODO add collision with pawn
// Function that is called when the projectile hits something.
void ADefaultBullet::OnHit( UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit )
{
	if ( OtherActor != this && OtherComponent->IsSimulatingPhysics() )
	{
		OtherComponent->AddImpulseAtLocation( ProjectileMovementComponent->Velocity * 100.0f, Hit.ImpactPoint );
	}
}

