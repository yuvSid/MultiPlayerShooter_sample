// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Engine/Engine.h"

#include "MultiPlayerShooterGameModeBase.generated.h"

UCLASS()
class MULTIPLAYERSHOOTER_API AMultiPlayerShooterGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void StartPlay() override;
};
