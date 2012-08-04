#pragma once
#include "AStarAlgorithm.h"

class DijkstraAlgorithm: public AbstractSearchAlgorithm
{
public:
	std::vector<GameState> FindPath(const GameRules &gameRules, GameState &startState);
	std::string ToString();
};

