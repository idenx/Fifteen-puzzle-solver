#pragma once
#include "AbstractSearchAlgorithm.h"
#include "BreadthFirstAlgorithm.h"

class BidirectBreadthFirstAlgorithm: public AbstractSearchAlgorithm
{
private:
	HashTableType nodesStartHashTable, nodesFinishHashTable;
public:
	std::vector<GameState> FindPath(const GameRules &gameRules, GameState &startState);
	std::string ToString();
	~BidirectBreadthFirstAlgorithm();
};

