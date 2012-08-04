#pragma once
#include <vector>
#include <intsafe.h>
#include "MoveDirections.h"

class GameState
{
private:
	std::vector<size_t> gameField;
	GameState* parentState;
	size_t H;
	size_t G;
	mutable UINT64 cachedHash;
	moveDirections currentDirection;
public:
	GameState();
	GameState(GameState *parentState, moveDirections moveDirection);
	void RecursivelyDispose();
	inline bool operator==(const GameState& comparingState) const { return (comparingState.GetHash() == this->GetHash()); }
	inline bool operator!=(const GameState& comparingState) const { return (comparingState.GetHash() != this->GetHash()); }

	inline size_t GetG() const { return G; }
	inline size_t GetH() const { return H; }
	inline std::vector<size_t> GetField() const { return gameField; }
	inline GameState* GetParent() const { return parentState; }
	inline moveDirections GetMoveDirection() const { return currentDirection; }
	UINT64 GetHash() const;

	inline void SetMoveDirection(moveDirections newMoveDirection) { currentDirection = newMoveDirection; }
	inline void SetG(size_t newG) { this->G = newG; }
	inline void SetH(size_t newH) { this->H = newH; }
	inline void SetField(std::vector<size_t> newField) { gameField = newField; }
	inline void SetParent(GameState *parentState) { this->parentState = parentState; }
};

struct DestructGameState
{
	void operator()(GameState *gameState)
	{
		gameState->RecursivelyDispose();
		delete gameState;
	}
};