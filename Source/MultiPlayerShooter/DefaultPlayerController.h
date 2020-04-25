// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DefaultCharacterFPS.h"

#include "DefaultPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERSHOOTER_API ADefaultPlayerController : public APlayerController
{
	GENERATED_BODY()

	ADefaultPlayerController();

protected:
	/** Allows the PlayerController to set up custom input bindings. */
	virtual void SetupInputComponent();

	virtual void OnPossess( APawn* aPawn ) override;
	
	UFUNCTION( NetMulticast, reliable )
	virtual void ChangeAttachedPawn();

	ADefaultCharacterFPS* currentControlledCharacter;

	//Movament functions
	//TODO add crouch
	UFUNCTION()
	void MoveYaw( float value = 1.0f );
	UFUNCTION()
	void MovePitch( float value = 1.0f );
	UFUNCTION()
	void MoveForward( float value = 1.0f );
	UFUNCTION()
	void MoveRight( float value = 1.0f );
	UFUNCTION()
	void StartJump();
	UFUNCTION()
	void StopJump();
	UFUNCTION()
	void StartCrouch();
	UFUNCTION()
	void StopCrouch();
	UFUNCTION()
	void FireWeapon(); //TODO implement through parent class, it has spectator and frozen settings
};
