#pragma once
#include "GameState.h"

class GameRules
{
private:
	static const size_t ZERO_CELL = 0;
	std::vector<moveDirections> permittedMoves;
	size_t fieldSize;
	void MakeMoveInDirection(GameState *gameState, const moveDirections &currentDirection) const;
	bool isMovePossible(const GameState *gameState, const moveDirections &currentDirection) const;
	void SwapGameElements(GameState *gameState, size_t firstIndex, size_t secondIndex) const;

public:
	bool EnableHeuristic;
	std::vector<GameState*> GetNeighborStates(GameState *gameState) const;
	size_t CalculateH(const GameState &gameState) const;
	static size_t CalculateInversionsCount(const GameState &gameState);
	GameState& GetFinalState() const;
	std::string GameStateToString(const GameState &gameState) const;
	GameRules(size_t fieldSize);
};

