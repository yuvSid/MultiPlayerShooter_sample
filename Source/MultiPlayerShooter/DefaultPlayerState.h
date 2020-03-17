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

protected:
	/** Player's current score. */
	UPROPERTY( replicatedUsing = OnRep_KillScore )
	int32 KillScore;

	UPROPERTY( replicatedUsing = OnRep_DeathScore )
	int32 DeathScore;

	UFUNCTION( BlueprintImplementableEvent, Category = "Score" )
	void ScoreChangeNotification();

public:
	void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	
	/** Replication Notification Callbacks */
	UFUNCTION()
	void OnRep_KillScore();
	UFUNCTION()
	void OnRep_DeathScore();

	UFUNCTION()
	void IncreaseKillScore() { KillScore++; }
};
