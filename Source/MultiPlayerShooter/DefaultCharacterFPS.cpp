// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultCharacterFPS.h"
#include "DefaultPlayerState.h"

#include "Math/UnrealMathUtility.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Pawn.h"
#include "Net/UnrealNetwork.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "Components/InputComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Camera/CameraComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"

#include "GameFramework/PlayerState.h"

// Sets default values
ADefaultCharacterFPS::ADefaultCharacterFPS()
{
	bReplicates = true;
	SetReplicatingMovement( true );
	
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a first person camera component.
	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>( TEXT( "FirstPersonCamera" ) );
	// Attach the camera component to our capsule component.
	FirstPersonCamera->SetupAttachment( GetCapsuleComponent() );

	// Position the camera slightly above the eyes.
	FirstPersonCamera->SetRelativeLocation( FVector( 0.0f, 0.0f, BaseEyeHeight ) );
	// Allow the pawn to control camera rotation.
	FirstPersonCamera->bUsePawnControlRotation = true;

	// The owning player doesn't see the regular (third-person) body mesh.
	GetMesh()->SetOwnerNoSee( true );
	GetMesh()->bCastDynamicShadow = false;
	GetMesh()->CastShadow = false;
	
	// Create a first person mesh component for the owning player.
	FirstPersonMesh = CreateDefaultSubobject<USkeletalMeshComponent>( TEXT( "FirstPersonMesh" ) );
	// Only the owning player sees this mesh.
	FirstPersonMesh->SetOnlyOwnerSee( true );
	// Attach the FPS mesh to the FPS camera.
	FirstPersonMesh->SetupAttachment( FirstPersonCamera );
	// Disable some environmental shadowing to preserve the illusion of having a single mesh.
	FirstPersonMesh->bCastDynamicShadow = false;
	FirstPersonMesh->CastShadow = false;

	//Initialize the player's Health
	MaxHealth = 100.0f;
	CurrentHealth = MaxHealth;


	//Initialize projectile class
	BulletClass = ADefaultBullet::StaticClass();
	//Initialize fire rate
	FireRate = 0.25f;
	bIsFiringWeapon = false;
}

void ADefaultCharacterFPS::BeginPlay()
{
	Super::BeginPlay();

	if (GetLocalRole() == ROLE_Authority) {
		DefaultSpawnLocation = GetActorLocation();
		DefaultSpawnRotation = GetActorRotation();
	}
		
}

void ADefaultCharacterFPS::MoveYaw( float value )	{	AddControllerYawInput( value );	}

void ADefaultCharacterFPS::MovePitch( float value )	{	AddControllerPitchInput( value );	}

void ADefaultCharacterFPS::MoveForward( float value )
{
	FVector Direction = FRotationMatrix( Controller->GetControlRotation() ).GetScaledAxis( EAxis::X );
	AddMovementInput( Direction, value );
}
void ADefaultCharacterFPS::MoveRight( float value )
{
	FVector Direction = FRotationMatrix( Controller->GetControlRotation() ).GetScaledAxis( EAxis::Y );
	AddMovementInput( Direction, value );
}

void ADefaultCharacterFPS::StartJump()	{	bPressedJump = true;	}

void ADefaultCharacterFPS::StopJump()	{	bPressedJump = false;	}

//TODO implement crouch animation in character BP
void ADefaultCharacterFPS::StartCrouch()	{	bIsCrouched = true;	}

void ADefaultCharacterFPS::StopCrouch()	{	bIsCrouched = false;	}

// Replicated Properties
void ADefaultCharacterFPS::GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const
{
	Super::GetLifetimeReplicatedProps( OutLifetimeProps );

	//Replicate current health.
	DOREPLIFETIME( ADefaultCharacterFPS, CurrentHealth );
}


void ADefaultCharacterFPS::OnRep_CurrentHealth()
{
	OnHealthUpdate();
}

void ADefaultCharacterFPS::SetCurrentHealth( float healthValue, AController* EventInstigator )
{
	if ( GetLocalRole() == ROLE_Authority )	{
		CurrentHealth = FMath::Clamp( healthValue, 0.f, MaxHealth );
		if ( CurrentHealth != 0.f ) {
			OnHealthUpdate();
		}			
		else {
			OnCharacterDeath( EventInstigator );
		}
		
	}
}

void ADefaultCharacterFPS::OnHealthUpdate()
{
	//Client-specific functionality
	if ( IsLocallyControlled() ) {
		HealthChangeNotification( GetCurrentHealth(), GetMaxHealth() );
	}

	//Server-specific functionality
	if ( GetLocalRole() == ROLE_Authority )	{
		;
	}

	//Functions that occur on all machines. 
	/*
		Any special functionality that should occur as a result of damage or death should be placed here.
	*/
}

void ADefaultCharacterFPS::OnCharacterDeath( AController* EventInstigator )
{
	if (GetLocalRole() == ROLE_Authority) {
		SetActorLocation( DefaultSpawnLocation );
		GetController()->ClientSetRotation( DefaultSpawnRotation );
		SetCurrentHealth( MaxHealth, EventInstigator );
		FString healthMessage = FString::Printf(TEXT("%s has been killed by %s"), *GetFName().ToString(), *EventInstigator->GetPlayerState< APlayerState >()->GetPlayerName() );
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, healthMessage);
		EventInstigator->GetPlayerState<ADefaultPlayerState>()->IncreaseKillScore();
	}
	if ( IsLocallyControlled() ) {
		DeathNotificationUI( true );
	}		
}

float ADefaultCharacterFPS::TakeDamage( float DamageTaken, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser )
{
	float damageApplied = CurrentHealth - DamageTaken;
	
	SetCurrentHealth( damageApplied, EventInstigator );
	return damageApplied;
}

//TODO transfer this to weapons class with different fire propeties, laser gun, automatic gun and one bullet gun like this now
void ADefaultCharacterFPS::StartFire()
{
	if ( !bIsFiringWeapon )	{
		bIsFiringWeapon = true;
		GetWorld()->GetTimerManager().SetTimer( FiringTimer, this, &ADefaultCharacterFPS::StopFire, FireRate, false );
		HandleFire();
	}
}

void ADefaultCharacterFPS::StopFire()
{
	bIsFiringWeapon = false;
}

void ADefaultCharacterFPS::HandleFire_Implementation() //TODO add _Implementation
{
	// Attempt to fire a Bullet.
	if ( BulletClass ) {
		// Get the camera transform.
		FVector CameraLocation;
		FRotator CameraRotation;
		GetActorEyesViewPoint( CameraLocation, CameraRotation );

		// Transform MuzzleOffset from camera space to world space.
		FVector MuzzleLocation = CameraLocation + FTransform( CameraRotation ).TransformVector( MuzzleOffset ); //TODO change bullet start location
		FRotator MuzzleRotation = CameraRotation;
		// Skew the aim to be slightly upwards.
		/*MuzzleRotation.Pitch += 10.0f;*/


		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();
		// Spawn the bullet at the muzzle.
		ADefaultBullet* Bullet = GetWorld()->SpawnActor<ADefaultBullet>( BulletClass, MuzzleLocation, MuzzleRotation, SpawnParams );
		if ( Bullet ) {
			Bullet->FireInDirection( MuzzleRotation.Vector() );
		}

	}	
}




