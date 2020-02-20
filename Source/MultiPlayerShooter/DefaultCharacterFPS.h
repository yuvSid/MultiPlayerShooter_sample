// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DefaultBullet.h"

#include "DefaultCharacterFPS.generated.h"

UCLASS()
class MULTIPLAYERSHOOTER_API ADefaultCharacterFPS : public ACharacter
{
	GENERATED_BODY()

public:	
	ADefaultCharacterFPS();

protected:
	
	virtual void BeginPlay() override;

	UPROPERTY( Native )
	FVector DefaultSpawnLocation;
	UPROPERTY(Native)
	FRotator DefaultSpawnRotation;
	
	UPROPERTY( EditDefaultsOnly, Category = "Health" )
	float MaxHealth;
	
	UPROPERTY( ReplicatedUsing = OnRep_CurrentHealth )
	float CurrentHealth;
	
	UFUNCTION()
	void OnRep_CurrentHealth();
	UFUNCTION()
	void OnHealthUpdate();
	UFUNCTION()
	void OnCharacterDeath();

	UPROPERTY( EditDefaultsOnly, Category = "Gameplay|Bullet" )
	TSubclassOf<class ADefaultBullet> BulletClass;

	
	UPROPERTY( EditDefaultsOnly, Category = "Gameplay" )
	float FireRate;
	UPROPERTY( Native )
	FTimerHandle FiringTimer;
	UPROPERTY(Native)
	bool bIsFiringWeapon;
	
	UFUNCTION( BlueprintCallable, Category = "Gameplay" )
	void StartFire();
	UFUNCTION( BlueprintCallable, Category = "Gameplay" )
	void StopFire();
	UFUNCTION( Server, Reliable )
	void HandleFire();

	

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "UMG Game" )
	TSubclassOf<UUserWidget> StartingUIWidget;
	UPROPERTY()
	class UUserWidget* CurrentUIWIdget;
	UFUNCTION( BlueprintCallable, Category = "UMG Game" )
	FORCEINLINE UUserWidget* GetCurrentUIWidget() { return CurrentUIWIdget; }

public:	
	void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UFUNCTION()
	void MoveForward( float Value );
	UFUNCTION()
	void MoveRight( float Value );
	UFUNCTION()
	void StartJump();
	UFUNCTION()
	void StopJump();	

	
	UPROPERTY( VisibleAnywhere )
	class UCameraComponent* FirstPersonCamera;

	UPROPERTY( VisibleDefaultsOnly, Category = Mesh )
	class USkeletalMeshComponent* FirstPersonMesh;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = Gameplay )
	FVector MuzzleOffset;

	// Getter for Max Health.
	UFUNCTION( BlueprintPure, Category = "Health" )
	FORCEINLINE float GetMaxHealth() const { return MaxHealth; }

	// Getter for Current Health.
	UFUNCTION( BlueprintPure, Category = "Health" )
	FORCEINLINE float GetCurrentHealth() const { return CurrentHealth; }

	// Event for blueprint health change
	UFUNCTION( BlueprintImplementableEvent, Category = "Health" )
	void HealthChangeNotification( float healthValue, float maxHealthValue );

	// Setter for Current Health. Clamps the value between 0 and MaxHealth and calls OnHealthUpdate. Should only be called on the server.
	UFUNCTION( BlueprintCallable, Category = "Health" )
	void SetCurrentHealth( float healthValue );

	// Event for taking damage. Overridden from APawn.
	UFUNCTION( BlueprintCallable, Category = "Health" )
	float TakeDamage( float DamageTaken, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser ) override;

	//Change or delete at all UMG.
	UFUNCTION( BlueprintCallable, Category = "UMG Game" )
	void ChangeWidgetUI( TSubclassOf<UUserWidget> NewUIWidgetClass );
};
