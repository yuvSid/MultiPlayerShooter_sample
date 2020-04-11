// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultPlayerController.h"

ADefaultPlayerController::ADefaultPlayerController()
	:Super()
{
	currentControlledCharacter = GetPawn< ADefaultCharacterFPS >();
}

void ADefaultPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis( "Turn", this, &ADefaultPlayerController::MoveYaw );
	InputComponent->BindAxis( "LookUp", this, &ADefaultPlayerController::MovePitch );
	InputComponent->BindAxis( "MoveForward", this, &ADefaultPlayerController::MoveForward );
	InputComponent->BindAxis( "MoveRight", this, &ADefaultPlayerController::MoveRight );
	InputComponent->BindAction( "Jump", IE_Pressed, this, &ADefaultPlayerController::StartJump );
	InputComponent->BindAction( "Jump", IE_Released, this, &ADefaultPlayerController::StopJump );
	InputComponent->BindAction( "Crouch", IE_Pressed, this, &ADefaultPlayerController::StartCrouch ); //TODO add Crouch to button bindings in project
	InputComponent->BindAction( "Crouch", IE_Released, this, &ADefaultPlayerController::StopCrouch );

	InputComponent->BindAction( "Fire", IE_Pressed, this, &ADefaultPlayerController::FireWeapon ); //TODO portal this to playerinput
}

void ADefaultPlayerController::MoveYaw( float value )
{
	if ( currentControlledCharacter )
		currentControlledCharacter->MoveYaw( value );
}

void ADefaultPlayerController::MovePitch( float value )
{
	if ( currentControlledCharacter )
		currentControlledCharacter->MovePitch( value );
}

void ADefaultPlayerController::MoveForward( float value )
{
	if ( currentControlledCharacter )
		currentControlledCharacter->MoveForward( value );
}

void ADefaultPlayerController::MoveRight( float value )
{
	if ( currentControlledCharacter )
		currentControlledCharacter->MoveRight( value );
}

void ADefaultPlayerController::StartJump()
{
	if ( currentControlledCharacter )
		currentControlledCharacter->StartJump();
}

void ADefaultPlayerController::StopJump()
{
	if ( currentControlledCharacter )
		currentControlledCharacter->StartJump();
}

void ADefaultPlayerController::StartCrouch()
{
	if ( currentControlledCharacter )
		currentControlledCharacter->StartCrouch();
}

void ADefaultPlayerController::StopCrouch()
{
	if ( currentControlledCharacter )
		currentControlledCharacter->StopCrouch();
}

void ADefaultPlayerController::FireWeapon()
{
	if ( currentControlledCharacter )
		currentControlledCharacter->StartFire();
}


