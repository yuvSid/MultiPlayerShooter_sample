// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultPlayerState.h"
#include "Net/UnrealNetwork.h"

ADefaultPlayerState::ADefaultPlayerState()
	: APlayerState()
{
	KillScore = 0;
	DeathScore = 0;
}

void ADefaultPlayerState::GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const
{
	Super::GetLifetimeReplicatedProps( OutLifetimeProps );

	DOREPLIFETIME( ADefaultPlayerState, KillScore );
	DOREPLIFETIME( ADefaultPlayerState, DeathScore );
}

void ADefaultPlayerState::OnRep_KillScore()
{
	if ( GetLocalRole() == ROLE_Authority ) {
		ScoreChangeNotification();
	}
}

void ADefaultPlayerState::OnRep_DeathScore()
{
}


