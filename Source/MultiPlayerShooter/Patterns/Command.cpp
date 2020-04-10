#include "Command.h"

void MoveForwardCommand::Execute( ADefaultCharacterFPS* const movableActor )
{
	movableActor->MoveForward();
}

void MoveForwardCommand::Abandon( ADefaultCharacterFPS* const movableActor ) {}

void MoveRightCommand::Execute( ADefaultCharacterFPS* const movableActor )
{
	movableActor->MoveRight();
}

void MoveRightCommand::Abandon( ADefaultCharacterFPS* const movableActor ) {}

void TurnCommand::Execute( ADefaultCharacterFPS* const movableActor )
{
}

void TurnCommand::Abandon( ADefaultCharacterFPS* const movableActor ) {}

void LookUpCommand::Execute( ADefaultCharacterFPS* const movableActor )
{
}

void LookUpCommand::Abandon( ADefaultCharacterFPS* const movableActor ) {}

void JumpCommand::Execute( ADefaultCharacterFPS* const movableActor )
{
	movableActor->StartJump();
}

void JumpCommand::Abandon( ADefaultCharacterFPS* const movableActor )
{
	movableActor->StopJump();
}

void FireCommand::Execute( ADefaultCharacterFPS* const movableActor )
{
}

void FireCommand::Abandon( ADefaultCharacterFPS* const movableActor ) {}
