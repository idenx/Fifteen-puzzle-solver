#pragma once
#include "GameRules.h"
#include "GameState.h"
#include "AbstractSearchAlgorithm.h"
#include "PathGetter.h"

struct GameStatesComparer: public std::binary_function<GameState*, GameState*, bool>
{
	bool operator() (const GameState* firstState, const GameState* secondState)
	{
		return (firstState->GetG() + firstState->GetH() > secondState->GetG() + secondState->GetH());
	}
};

class AStarAlgorithm: public AbstractSearchAlgorithm
{
private:
	typedef std::priority_queue<GameState*, std::vector<GameState*>, GameStatesComparer> heapType;

	heapType openStatesHeap;
public:
	std::vector<GameState> FindPath(const GameRules &gameRules, GameState &startState);
	std::string ToString();
	~AStarAlgorithm();
};

