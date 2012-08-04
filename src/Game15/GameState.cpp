#include "GameState.h"

GameState::GameState(GameState *parentState, moveDirections moveDirection)
{
	this->gameField = std::vector<size_t>(parentState->gameField.begin(), parentState->gameField.end());
	this->parentState = parentState;
	this->G = parentState->GetG() + 1;
	this->cachedHash = 0;
	this->currentDirection = moveDirection;
}

GameState::GameState()
{
	this->G = 0;
	this->parentState = 0;
	this->cachedHash = 0;
	this->currentDirection = EMPTY;
}

void GameState::RecursivelyDispose()
{
	static const GameState *BAD_ADDRESS = (GameState*)0xfeeefeee;
	if (parentState != 0)
	{
		if (parentState->parentState != BAD_ADDRESS && parentState->parentState != 0)
		{
			parentState->RecursivelyDispose();
			delete parentState;
		}
	}
}

UINT64 GameState::GetHash() const
{
 	if (cachedHash != 0)
 	{		
 		return cachedHash;
 	}
 	else
 	{
		UINT64 hash = 0;
		UINT64 temp;
		for (size_t index = 0; index < gameField.size(); ++index)
		{	
			temp = gameField[index];
			hash |= temp << (index * 4);
		}
		this->cachedHash = hash;
		return hash;
	}
}