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

	
}

// Called when the game starts or when spawned
void ADefaultCharacterFPS::BeginPlay()
{
	Super::BeginPlay();
	
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

