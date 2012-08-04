#include "DijkstraAlgorithm.h"

std::vector<GameState> DijkstraAlgorithm::FindPath(const GameRules &gameRules, GameState &startState)
{
	AStarAlgorithm aStarAlgorithm;
	GameRules DijkstraRules = GameRules(gameRules);
	DijkstraRules.EnableHeuristic = false;
	return aStarAlgorithm.FindPath(DijkstraRules, startState);
}

std::string DijkstraAlgorithm::ToString()
{
	return "Dijkstra";
}