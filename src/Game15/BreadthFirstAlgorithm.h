#pragma once
#include "AbstractSearchAlgorithm.h"
#include "PathGetter.h"

typedef std::unordered_set<GameState*> HashTableType;

template<>
struct std::hash<GameState*>
{
	size_t operator()(const GameState *toHash) const
	{
		return std::hash<UINT64>()(toHash->GetHash());
	}
};

template<>
struct std::equal_to<GameState*>
{
	bool operator()(const GameState *firstState, const GameState *secondState) const
	{
		return *firstState == *secondState;
	}
};

inline void ProcessNeighborsOfCurrentState(std::unordered_set<UINT64> &usedNodes, std::deque<GameState*> &nodesQueue, const GameRules &gameRules,
	GameState *currentState, HashTableType &nodesHashTable);

class BreadthFirstAlgorithm: public AbstractSearchAlgorithm
{
private:
	std::deque<GameState*> nodesQueue;
public:
	std::vector<GameState> FindPath(const GameRules &gameRules, GameState &startState);
	std::string ToString();
	~BreadthFirstAlgorithm();
};

