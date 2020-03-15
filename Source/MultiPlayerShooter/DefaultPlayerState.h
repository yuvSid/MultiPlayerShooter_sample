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

public:
	/** Replication Notification Callbacks */
	virtual void OnRep_Score() override;

};
