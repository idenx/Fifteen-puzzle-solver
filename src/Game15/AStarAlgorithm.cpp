#include "AStarAlgorithm.h"

AStarAlgorithm::~AStarAlgorithm()
{
// 	DestructGameState destructor;
// 	GameState *tempState;
// 	while (!openStatesHeap.empty())
// 	{
// 		tempState = openStatesHeap.top();
// 		openStatesHeap.pop();
// 		destructor(tempState);
// 	}
}

std::vector<GameState> AStarAlgorithm::FindPath(const GameRules &gameRules, GameState &startState)
{
	GameState finalState = gameRules.GetFinalState();
 	std::unordered_set<UINT64> openStatesHashTable, closedStatesHashTable;
	startState.SetG(0);
	startState.SetH(gameRules.CalculateH(startState));
	openStatesHeap.push(&startState);
	openStatesHashTable.insert(startState.GetHash());

	while (!openStatesHeap.empty())
	{
		GameState* currentState = openStatesHeap.top();
		if (*currentState == finalState)
		{
			return GetPath(*currentState, finalState);
		}
		openStatesHeap.pop();
		closedStatesHashTable.insert(currentState->GetHash());
		std::vector<GameState*> neighborStates = gameRules.GetNeighborStates(currentState);
		for (std::vector<GameState*>::const_iterator currentNeighborIterator = neighborStates.begin(); 
			currentNeighborIterator != neighborStates.end(); ++currentNeighborIterator)
		{
			GameState *currentNeighbor = *currentNeighborIterator;
			currentNeighbor->SetH(gameRules.CalculateH(*currentNeighbor));
			if (closedStatesHashTable.find(currentNeighbor->GetHash()) != closedStatesHashTable.end())	
				continue;
			if (openStatesHashTable.find(currentNeighbor->GetHash()) == openStatesHashTable.end())
			{
				openStatesHeap.push(currentNeighbor);
				openStatesHashTable.insert(currentNeighbor->GetHash());
			}
			else
			{
				if (currentState->GetG() + 1 < currentNeighbor->GetG())
				{
					currentNeighbor->SetParent(currentState);
					currentNeighbor->SetG(currentState->GetG() + 1);
				}
			}
		}
	}
	return std::vector<GameState>();
}

std::string AStarAlgorithm::ToString()
{
	return "A*";
}
