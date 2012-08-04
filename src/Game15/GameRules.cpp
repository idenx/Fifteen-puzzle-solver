#include "GameRules.h"
#include <algorithm>
#include <sstream>

GameRules::GameRules(size_t fieldSize)
{
	this->fieldSize = fieldSize;
	this->EnableHeuristic = true;
	permittedMoves = std::vector<moveDirections>();
	permittedMoves.push_back(UP);
	permittedMoves.push_back(DOWN);
	permittedMoves.push_back(LEFT);
	permittedMoves.push_back(RIGHT);
}

std::vector<GameState*> GameRules::GetNeighborStates(GameState *gameState) const
{
	std::vector<GameState*> neighborStates;
	for (std::vector<moveDirections>::const_iterator currentMove = permittedMoves.begin(); currentMove != permittedMoves.end(); ++currentMove)
	{
		if (isMovePossible(gameState, *currentMove))
		{
			GameState* newChildState = new GameState(gameState, *currentMove);
			MakeMoveInDirection(newChildState, *currentMove);
			neighborStates.push_back(newChildState);
		}
	}
	return neighborStates;
}

void GameRules::MakeMoveInDirection(GameState *gameState, const moveDirections &currentDirection) const
{
	std::vector<size_t> gameField = gameState->GetField();
	size_t emptyCellPosition = find(gameField.begin(), gameField.end(), ZERO_CELL) - gameField.begin();
	switch(currentDirection)
	{
		case DOWN:
			SwapGameElements(gameState, emptyCellPosition, emptyCellPosition - fieldSize);
			break;
		case UP:
			SwapGameElements(gameState, emptyCellPosition, emptyCellPosition + fieldSize);
			break;
		case LEFT:
			SwapGameElements(gameState, emptyCellPosition, emptyCellPosition + 1);
			break;
		case RIGHT:
			SwapGameElements(gameState, emptyCellPosition, emptyCellPosition - 1);
			break;
	}
}

void GameRules::SwapGameElements(GameState *gameState, size_t firstIndex, size_t secondIndex) const
{
	std::vector<size_t> gameField = gameState->GetField();
	size_t tempElement = gameField[firstIndex];
	gameField[firstIndex] = gameField[secondIndex];
	gameField[secondIndex] = tempElement;
	gameState->SetField(gameField);
}

bool GameRules::isMovePossible(const GameState *gameState, const moveDirections &currentDirection) const
{
	std::vector<size_t> gameField = gameState->GetField();
	size_t emptyCellPosition = find(gameField.begin(), gameField.end(), ZERO_CELL) - gameField.begin();
	switch(currentDirection)
	{
	case DOWN:
		return (emptyCellPosition >= fieldSize);
	case UP:
		return (fieldSize * fieldSize - emptyCellPosition > fieldSize);
	case RIGHT:
		return (emptyCellPosition % fieldSize != 0);
	case LEFT:
		return (emptyCellPosition % fieldSize != fieldSize - 1);
	};
	return false;
}

size_t GameRules::CalculateH(const GameState &gameState) const
{
	if (EnableHeuristic)
	{
		std::vector<size_t> gameField = gameState.GetField();
		size_t errorDistance = 0;
		size_t zeroPosition;
		for (size_t currentIndex = 0; currentIndex < gameField.size(); ++currentIndex)
		{
			size_t currentElement = gameField[currentIndex];
			if (currentElement != currentIndex + 1)
			{
				if (currentElement != ZERO_CELL)
				{
					errorDistance += (abs((int)((currentElement - 1) / fieldSize - currentIndex / fieldSize))) +
						(abs((int)((currentElement - 1) % fieldSize - currentIndex % fieldSize)));
				}
				else
				{
					zeroPosition = currentIndex;
				}
			}
		}
		errorDistance += (abs((int)((fieldSize - 1) - (zeroPosition / fieldSize)))) +
						(abs((int)((fieldSize - 1) - (zeroPosition % fieldSize))));

		return errorDistance;
	}
	else
	{
		return 0;
	}
}

GameState& GameRules::GetFinalState() const
{
	GameState* finalState = new GameState();
	std::vector<size_t> finalField = std::vector<size_t>();
	finalField.reserve(fieldSize * fieldSize);
	for (size_t currentElement = 1; currentElement < fieldSize * fieldSize; ++currentElement)
	{
		finalField.push_back(currentElement);
	}
	finalField.push_back(ZERO_CELL);
	finalState->SetField(finalField);
	return *finalState;
}

size_t GameRules::CalculateInversionsCount(const GameState &gameState)
{
	size_t inversionsCount = 0;
	std::vector<size_t> gameField = gameState.GetField();
	for (std::vector<size_t>::const_iterator fieldIterator1 = gameField.begin(); fieldIterator1 != gameField.end() - 1; ++fieldIterator1)
	{
		for (std::vector<size_t>::const_iterator fieldIterator2 = fieldIterator1 + 1; fieldIterator2 != gameField.end(); ++fieldIterator2)
		{
			if (*fieldIterator1 > *fieldIterator2)
			{
				++inversionsCount;
			}
		}
	}
	return inversionsCount - gameField.size() + 1;
}

std::string GameRules::GameStateToString(const GameState &gameState) const
{
	std::ostringstream  stringStream;
	std::vector<size_t> gameField = gameState.GetField();
	for (size_t currentIndex = 0; currentIndex < fieldSize * fieldSize; ++currentIndex)
	{
 		if (currentIndex % fieldSize == 0)
 			stringStream << std::endl;
		if (gameField[currentIndex] < 10)
			stringStream << " " << gameField[currentIndex] << "  ";
		else
			stringStream << gameField[currentIndex] << "  ";
	}
	return stringStream.str();
}
