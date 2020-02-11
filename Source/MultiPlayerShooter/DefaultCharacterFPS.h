// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
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

#include "DefaultBullet.h"

#include "DefaultCharacterFPS.generated.h"

UCLASS()
class MULTIPLAYERSHOOTER_API ADefaultCharacterFPS : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADefaultCharacterFPS();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** The player's maximum health. This is the highest that their health can be, and the value that their health starts at when spawned.*/
	UPROPERTY( EditDefaultsOnly, Category = "Health" )
	float MaxHealth;

	/** The player's current health. When reduced to 0, they are considered dead.*/
	UPROPERTY( ReplicatedUsing = OnRep_CurrentHealth )
	float CurrentHealth;

	/** RepNotify for changes made to current health.*/
	UFUNCTION()
	void OnRep_CurrentHealth();

	//Response to health being updated. Called on the server immediately after modification, and on clients in response to a RepNotify
	void OnHealthUpdate();

	//UPROPERTY( EditDefaultsOnly, Category = "Gameplay|Bullet" )
	//TSubclassOf<class ADefaultBullet> BulletClass;

	/** Delay between shots in seconds. Used to control fire rate for our test projectile, but also to prevent an overflow of server functions from binding SpawnProjectile directly to input.*/
	UPROPERTY( EditDefaultsOnly, Category = "Gameplay" )
	float FireRate;

	/** If true, we are in the process of firing projectiles. */
	bool bIsFiringWeapon;

	/** Function for beginning weapon fire.*/
	UFUNCTION( BlueprintCallable, Category = "Gameplay" )
	void StartFire();

	/** Function for ending weapon fire. Once this is called, the player can use StartFire again.*/
	UFUNCTION( BlueprintCallable, Category = "Gameplay" )
	void StopFire();

	/** Server function for spawning projectiles.*/
	UFUNCTION( Server, Reliable )
	void HandleFire();

	/** A timer handle used for providing the fire rate delay in-between spawns.*/
	FTimerHandle FiringTimer;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Property replication
	void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Handles input for moving forward and backward.
	UFUNCTION()
	void MoveForward( float Value );

	// Handles input for moving right and left.
	UFUNCTION()
	void MoveRight( float Value );

	// Sets jump flag when key is pressed.
	UFUNCTION()
	void StartJump();

	// Clears jump flag when key is released.
	UFUNCTION()
	void StopJump();	

	// FPS camera.
	UPROPERTY( VisibleAnywhere )
	UCameraComponent* FirstPersonCamera;

	// First-person mesh (arms), visible only to the owning player.
	UPROPERTY( VisibleDefaultsOnly, Category = Mesh )
	USkeletalMeshComponent* FirstPersonMesh;

	// Gun muzzle's offset from the camera location.
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = Gameplay )
	FVector MuzzleOffset;

	// Bullet class to spawn.
	UPROPERTY( EditDefaultsOnly, Category = Bullets )
	TSubclassOf<class ADefaultBullet> BulletClass;

	// Getter for Max Health.
	UFUNCTION( BlueprintPure, Category = "Health" )
	FORCEINLINE float GetMaxHealth() const { return MaxHealth; }

	// Getter for Current Health.
	UFUNCTION( BlueprintPure, Category = "Health" )
	FORCEINLINE float GetCurrentHealth() const { return CurrentHealth; }

	// Setter for Current Health. Clamps the value between 0 and MaxHealth and calls OnHealthUpdate. Should only be called on the server.
	UFUNCTION( BlueprintCallable, Category = "Health" )
	void SetCurrentHealth( float healthValue );

	// Event for taking damage. Overridden from APawn.
	UFUNCTION( BlueprintCallable, Category = "Health" )
	float TakeDamage( float DamageTaken, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser ) override;
};
