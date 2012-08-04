#pragma once
#include "GameState.h"
#include "GameRules.h"

class AbstractSearchAlgorithm
{
public:
 	virtual std::vector<GameState> FindPath(const GameRules &gameRules, GameState &startState) = 0;
 	virtual std::string ToString() = 0;
};