#include "BreadthFirstAlgorithm.h"

BreadthFirstAlgorithm::~BreadthFirstAlgorithm()
{
	//std::for_each(nodesQueue.begin(), nodesQueue.end(), DestructGameState());
}

std::vector<GameState> BreadthFirstAlgorithm::FindPath(const GameRules &gameRules, GameState &startState)
{
	std::unordered_set<UINT64> usedNodes;
	HashTableType nodesHashTable;
	GameState finalState = gameRules.GetFinalState();
	nodesQueue.push_back(&startState);
	nodesHashTable.insert(&startState);
	GameState *currentState;
	while (!nodesQueue.empty())
	{
		currentState = nodesQueue.front();
		HashTableType::const_iterator findedState = nodesHashTable.find(&finalState);
		if (findedState != nodesHashTable.end())
		{
			return GetPath(**findedState, finalState);
		}
		nodesHashTable.erase(currentState);
		nodesQueue.pop_front();
		ProcessNeighborsOfCurrentState(usedNodes, nodesQueue, gameRules, currentState, nodesHashTable);
	}
	return std::vector<GameState>();
}

inline void ProcessNeighborsOfCurrentState(std::unordered_set<UINT64> &usedNodes, std::deque<GameState*> &nodesQueue, const GameRules &gameRules,
	GameState *currentState, HashTableType &nodesHashTable)
{
	std::vector<GameState*> neighborStates = gameRules.GetNeighborStates(currentState);
	for (std::vector<GameState*>::const_iterator currentNeighborIterator = neighborStates.begin(); 
		currentNeighborIterator != neighborStates.end(); ++currentNeighborIterator)
	{
		GameState *currentNeighbor = *currentNeighborIterator;
		if (usedNodes.find(currentNeighbor->GetHash()) == usedNodes.end())
		{
			usedNodes.insert(currentNeighbor->GetHash());
			nodesQueue.push_back(currentNeighbor);
			nodesHashTable.insert(currentNeighbor);
		}
	}
}

std::string BreadthFirstAlgorithm::ToString()
{
	return "BreadthFirst";
}