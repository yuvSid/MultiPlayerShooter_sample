// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Engine/Engine.h"

#include "MultiPlayerShooterGameModeBase.generated.h"

UCLASS()
class MULTIPLAYERSHOOTER_API AMultiPlayerShooterGameModeBase : public AGameMode
{
	GENERATED_BODY()

protected:
	virtual void StartPlay() override;
};
