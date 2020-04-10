#pragma once

#include "DefaultCharacterFPS.h"

class Command
{
	virtual void Execute( ADefaultCharacterFPS* const movableActor ) = 0;
	virtual void Abandon( ADefaultCharacterFPS* const movableActor ) = 0;
};

class MoveForwardCommand : public Command
{
	virtual void Execute( ADefaultCharacterFPS* const movableActor );
	virtual void Abandon( ADefaultCharacterFPS* const movableActor );
};

class MoveRightCommand : public Command
{
	virtual void Execute( ADefaultCharacterFPS* const movableActor );
	virtual void Abandon( ADefaultCharacterFPS* const movableActor );
};

class TurnCommand : public Command
{
	virtual void Execute( ADefaultCharacterFPS* const movableActor );
	virtual void Abandon( ADefaultCharacterFPS* const movableActor );
};

class LookUpCommand : public Command
{
	virtual void Execute( ADefaultCharacterFPS* const movableActor );
	virtual void Abandon( ADefaultCharacterFPS* const movableActor );
};

class JumpCommand : public Command
{
	virtual void Execute( ADefaultCharacterFPS* const movableActor );
	virtual void Abandon( ADefaultCharacterFPS* const movableActor );
};

class FireCommand : public Command
{
	virtual void Execute( ADefaultCharacterFPS* const movableActor );
	virtual void Abandon( ADefaultCharacterFPS* const movableActor );
};

