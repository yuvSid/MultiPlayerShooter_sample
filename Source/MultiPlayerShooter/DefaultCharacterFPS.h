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

	//Respawn defaul position
	//TODO delete or rewrite after change to repossess pawn
	UPROPERTY()
	FVector DefaultSpawnLocation;
	UPROPERTY()
	FRotator DefaultSpawnRotation;
	
	//Health propeties
	//TODO add blueprint change of maxHealth value as gamedesign propetie
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


	UFUNCTION( BlueprintImplementableEvent, Category = "Health" )
		void HealthChangeNotification( float healthValue, float maxHealthValue );
	UFUNCTION( BlueprintImplementableEvent, Category = "Health" )
		void DeathNotificationUI( bool isOn );

	UPROPERTY( EditDefaultsOnly, Category = "Gameplay|Bullet" )
	TSubclassOf<class ADefaultBullet> BulletClass;
	
	//Fire propetie
	//TODO add default damage propetie to change in blueprint
	UPROPERTY( EditDefaultsOnly, Category = "Gameplay" )
	float FireRate;
	UPROPERTY()
	FTimerHandle FiringTimer;
	UPROPERTY()
	bool bIsFiringWeapon;	
	UFUNCTION( BlueprintCallable, Category = "Gameplay" )
	void StartFire();
	UFUNCTION( BlueprintCallable, Category = "Gameplay" )
	void StopFire();
	UFUNCTION( Server, Reliable )
	void HandleFire();
	
	//Movament functions
	//TODO add crouch
	UFUNCTION()
	void MoveForward( float Value );
	UFUNCTION()
	void MoveRight( float Value );
	UFUNCTION()
	void StartJump();
	UFUNCTION()
	void StopJump();

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "UMG Game" )
	TSubclassOf<UUserWidget> StartingUIWidget;
	UPROPERTY()
	class UUserWidget* CurrentUIWIdget;
	UFUNCTION( BlueprintCallable, Category = "UMG Game" )
	void ChangeWidgetUI( TSubclassOf<UUserWidget> NewUIWidgetClass );	
	
	UPROPERTY( VisibleAnywhere )
	class UCameraComponent* FirstPersonCamera;
	UPROPERTY( VisibleDefaultsOnly, Category = Mesh )
	class USkeletalMeshComponent* FirstPersonMesh;
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = Gameplay )
	FVector MuzzleOffset;

public:
	void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

	virtual void SetupPlayerInputComponent( class UInputComponent* PlayerInputComponent ) override;

	UFUNCTION( BlueprintCallable, Category = "Health" )
	float TakeDamage( float DamageTaken, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser ) override;

	UFUNCTION( BlueprintPure, Category = "Health" )
	FORCEINLINE float GetMaxHealth() const { return MaxHealth; }
	UFUNCTION( BlueprintPure, Category = "Health" )
	FORCEINLINE float GetCurrentHealth() const { return CurrentHealth; }
	UFUNCTION( BlueprintCallable, Category = "Health" )
	void SetCurrentHealth( float healthValue );

	UFUNCTION( BlueprintCallable, Category = "UMG Game" )
	FORCEINLINE UUserWidget* GetCurrentUIWidget() { return CurrentUIWIdget; }
};
