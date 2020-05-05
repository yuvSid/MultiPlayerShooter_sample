// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultPlayerController.h"

ADefaultPlayerController::ADefaultPlayerController()
	:Super()
{
	bReplicates = true;
	bReplicateMovement = true;
	currentControlledCharacter = GetPawn< ADefaultCharacterFPS >();
}

void ADefaultPlayerController::GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const
{
	Super::GetLifetimeReplicatedProps( OutLifetimeProps );

	DOREPLIFETIME( ADefaultPlayerController, currentControlledCharacter );
}

//void ADefaultPlayerController::SetupInputComponent()
//{
//	Super::SetupInputComponent();
//
//	InputComponent->BindAxis( "Turn", currentControlledCharacter, &ADefaultCharacterFPS::MoveYaw );
//	InputComponent->BindAxis( "LookUp", currentControlledCharacter, &ADefaultCharacterFPS::MovePitch );
//	InputComponent->BindAxis( "MoveForward", currentControlledCharacter, &ADefaultCharacterFPS::MoveForward );
//	InputComponent->BindAxis( "MoveRight", currentControlledCharacter, &ADefaultCharacterFPS::MoveRight );
//	InputComponent->BindAction( "Jump", IE_Pressed, currentControlledCharacter, &ADefaultCharacterFPS::StartJump );
//	InputComponent->BindAction( "Jump", IE_Released, currentControlledCharacter, &ADefaultCharacterFPS::StopJump );
//	InputComponent->BindAction( "Crouch", IE_Pressed, currentControlledCharacter, &ADefaultCharacterFPS::StartCrouch ); //TODO add Crouch to button bindings in project
//	InputComponent->BindAction( "Crouch", IE_Released, currentControlledCharacter, &ADefaultCharacterFPS::StopCrouch );
//
//	InputComponent->BindAction( "Fire", IE_Pressed, currentControlledCharacter, &ADefaultCharacterFPS::StartFire ); //TODO portal this to playerinput
//}

void ADefaultPlayerController::OnPossess( APawn* aPawn )
{
	Super::OnPossess( aPawn );
	ChangeAttachedPawn( aPawn );
}

void ADefaultPlayerController::ChangeAttachedPawn( APawn* aPawn )
{
	verifyf( aPawn != nullptr, TEXT( "nullptr instead of new Pawn! ChangeAttachedPawn_Implementation, %s" ), *GetName() );
	aPawn->Controller = Cast< AController, ADefaultPlayerController >( this );
	verifyf( aPawn->Controller != nullptr, TEXT( "Something went wrong here %s! Terminating!" ), *GetName() );
	currentControlledCharacter = Cast< ADefaultCharacterFPS, APawn >( aPawn );
	verifyf( currentControlledCharacter != nullptr, TEXT( "Something went here with %s! Terminating!" ), *GetName() );
}


//TODO  if bind not works to changable character, uncomment this section
// {
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
		currentControlledCharacter->StopJump();
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
// }


