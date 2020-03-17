// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "DefaultPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERSHOOTER_API ADefaultPlayerState : public APlayerState
{
	GENERATED_BODY()

	ADefaultPlayerState();

	/** Player's current score. */
	UPROPERTY( replicatedUsing = OnRep_KillScore )
	int16 KillScore;

	UPROPERTY( replicatedUsing = OnRep_DeathScore )
	int16 DeathScore;

public:
	void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	
	/** Replication Notification Callbacks */
	UFUNCTION()
	void OnRep_KillScore();
	UFUNCTION()
	void OnRep_DeathScore();

};
