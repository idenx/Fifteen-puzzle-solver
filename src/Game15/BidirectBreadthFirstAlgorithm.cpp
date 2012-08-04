#include "BidirectBreadthFirstAlgorithm.h"
#include "PathGetter.h"

BidirectBreadthFirstAlgorithm::~BidirectBreadthFirstAlgorithm()
{
// 	std::for_each(nodesStartHashTable.begin(), nodesStartHashTable.end(), DestructGameState());
// 	std::for_each(nodesFinishHashTable.begin(), nodesFinishHashTable.end(), DestructGameState());
}

std::vector<GameState> BidirectBreadthFirstAlgorithm::FindPath(const GameRules &gameRules, GameState &startState)
{
	std::unordered_set<UINT64> usedNodesStart, usedNodesFinish;
	std::deque<GameState*> nodesQueueStart, nodesQueueFinish;
	GameState finalState = gameRules.GetFinalState();
	nodesQueueStart.push_back(&startState);
	nodesQueueFinish.push_back(&finalState);
	nodesStartHashTable.insert(&startState);
	nodesFinishHashTable.insert(&finalState);
	GameState *currentStateStart, *currentStateFinish;
	while (!nodesQueueStart.empty() && !nodesQueueFinish.empty())
	{
		currentStateStart = nodesQueueStart.front();
		currentStateFinish = nodesQueueFinish.front();
		HashTableType::const_iterator findedState = nodesStartHashTable.find(currentStateFinish);
		if (findedState != nodesStartHashTable.end())
		{
			return GetPath(**findedState, *currentStateFinish);
		}
		findedState = nodesFinishHashTable.find(currentStateStart);
		if (findedState != nodesFinishHashTable.end())
		{
			return GetPath(*currentStateStart, **findedState);
		}
		nodesStartHashTable.erase(currentStateStart);
		nodesFinishHashTable.erase(currentStateFinish);
		nodesQueueStart.pop_front();
		nodesQueueFinish.pop_front();
		ProcessNeighborsOfCurrentState(usedNodesStart, nodesQueueStart, gameRules, currentStateStart, nodesStartHashTable);
		ProcessNeighborsOfCurrentState(usedNodesFinish, nodesQueueFinish, gameRules, currentStateFinish, nodesFinishHashTable);
	}
	return std::vector<GameState>();
}

std::string BidirectBreadthFirstAlgorithm::ToString()
{
	return "Bidirectional BreadthFirst";
}