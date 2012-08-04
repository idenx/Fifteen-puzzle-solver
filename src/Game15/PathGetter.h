#pragma once
#include <unordered_set>
#include <queue>
#include "GameState.h"
#include "GameRules.h"

inline std::vector<GameState> GetPath(const GameState &gameStateStart, const GameState  &gameStateFinish)
{
	GameState* currentState = new GameState(gameStateStart);
	std::vector<GameState> resultPath;
	while (currentState->GetParent())
	{
		resultPath.push_back(*currentState);
		currentState = currentState->GetParent();
	}
	std::reverse(resultPath.begin(), resultPath.end());
	currentState = new GameState(gameStateFinish);
	while (currentState->GetParent())
	{
		currentState->SetMoveDirection(InvertMoveDirection(currentState->GetMoveDirection()));
		resultPath.push_back(*currentState);
		currentState = currentState->GetParent();
	}
	return resultPath;
}
