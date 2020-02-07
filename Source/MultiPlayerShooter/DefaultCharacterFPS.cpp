// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultCharacterFPS.h"

// Sets default values
ADefaultCharacterFPS::ADefaultCharacterFPS()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if ( GEngine )
	{
		// Put up a debug message for five seconds. The -1 "Key" value (first argument) indicates that we will never need to update or refresh this message.
		GEngine->AddOnScreenDebugMessage( -1, 5.0f, FColor::Red, TEXT( "We are using FPSCharacter." ) );
	}

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
}

// Called when the game starts or when spawned
void ADefaultCharacterFPS::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADefaultCharacterFPS::OnRep_CurrentHealth()
{
	OnHealthUpdate();
}

// Called every frame
void ADefaultCharacterFPS::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADefaultCharacterFPS::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up "movement" bindings.
	PlayerInputComponent->BindAxis( "MoveForward", this, &ADefaultCharacterFPS::MoveForward );
	PlayerInputComponent->BindAxis( "MoveRight", this, &ADefaultCharacterFPS::MoveRight );

	// Set up "look bindings"
	PlayerInputComponent->BindAxis( "Turn", this, &ADefaultCharacterFPS::AddControllerYawInput );
	PlayerInputComponent->BindAxis( "LookUp", this, &ADefaultCharacterFPS::AddControllerPitchInput );

	// Set up "action" bindings.
	PlayerInputComponent->BindAction( "Jump", IE_Pressed, this, &ADefaultCharacterFPS::StartJump );
	PlayerInputComponent->BindAction( "Jump", IE_Released, this, &ADefaultCharacterFPS::StopJump );

	PlayerInputComponent->BindAction( "Fire", IE_Pressed, this, &ADefaultCharacterFPS::Fire );
}

void ADefaultCharacterFPS::MoveForward( float Value )
{
	// Find out which way is "forward" and record that the player wants to move that way.
	FVector Direction = FRotationMatrix( Controller->GetControlRotation() ).GetScaledAxis( EAxis::X );
	AddMovementInput( Direction, Value );
}
void ADefaultCharacterFPS::MoveRight( float Value )
{
	// Find out which way is "forward" and record that the player wants to move that way.
	FVector Direction = FRotationMatrix( Controller->GetControlRotation() ).GetScaledAxis( EAxis::Y );
	AddMovementInput( Direction, Value );
}

void ADefaultCharacterFPS::StartJump()
{
	bPressedJump = true;
}

void ADefaultCharacterFPS::StopJump()
{
	bPressedJump = false;
}

// Replicated Properties
void ADefaultCharacterFPS::GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const
{
	Super::GetLifetimeReplicatedProps( OutLifetimeProps );

	//Replicate current health.
	DOREPLIFETIME( AThirdPersonMPCharacter, CurrentHealth );
}

void ADefaultCharacterFPS::OnHealthUpdate()
{
	//Client-specific functionality
	if ( IsLocallyControlled() )
	{
		FString healthMessage = FString::Printf( TEXT( "You now have %f health remaining." ), CurrentHealth );
		GEngine->AddOnScreenDebugMessage( -1, 5.f, FColor::Blue, healthMessage );

		if ( CurrentHealth <= 0 )
		{
			FString deathMessage = FString::Printf( TEXT( "You have been killed." ) );
			GEngine->AddOnScreenDebugMessage( -1, 5.f, FColor::Red, deathMessage );
		}
	}

	//Server-specific functionality
	if ( Role == ROLE_Authority )
	{
		FString healthMessage = FString::Printf( TEXT( "%s now has %f health remaining." ), *GetFName().ToString(), CurrentHealth );
		GEngine->AddOnScreenDebugMessage( -1, 5.f, FColor::Blue, healthMessage );
	}

	//Functions that occur on all machines. 
	/*
		Any special functionality that should occur as a result of damage or death should be placed here.
	*/
}

void ADefaultCharacterFPS::Fire()
{
	// Attempt to fire a Bullet.
	if ( BulletClass )
	{
		// Get the camera transform.
		FVector CameraLocation;
		FRotator CameraRotation;
		GetActorEyesViewPoint( CameraLocation, CameraRotation );

		// Transform MuzzleOffset from camera space to world space.
		FVector MuzzleLocation = CameraLocation + FTransform( CameraRotation ).TransformVector( MuzzleOffset ); //TODO change bullet start location
		FRotator MuzzleRotation = CameraRotation;
		// Skew the aim to be slightly upwards.
		MuzzleRotation.Pitch += 10.0f;
		UWorld* World = GetWorld();
		if ( World )
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;
			// Spawn the bullet at the muzzle.
			ADefaultBullet* Bullet = World->SpawnActor<ADefaultBullet>( BulletClass, MuzzleLocation, MuzzleRotation, SpawnParams );
			if ( Bullet )
			{
				// Set the projectile's initial trajectory.
				FVector LaunchDirection = MuzzleRotation.Vector();
				Bullet->FireInDirection( LaunchDirection );
			}
		}
	}
}

