// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultPlayerState.h"

ADefaultPlayerState::ADefaultPlayerState() 
	: Super()
{
	KillScore = 0;
	DeathScore = 0;
}

void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override
{
	Super:GetLifetimeReplicatedProps( OutLifetimeProps );

	DOREPLIFETIME( ADefaultPlayerState, KillScore );
	DOREPLIFETIME( ADefaultPlayerState, DeathScore );
}


void ADefaultPlayerState::OnRep_KillScore()
{
}

void ADefaultPlayerState::OnRep_DeathScore()
{
}


