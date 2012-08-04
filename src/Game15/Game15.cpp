#include "AStarAlgorithm.h"
#include "BidirectBreadthFirstAlgorithm.h"
#include "BreadthFirstAlgorithm.h"
#include "DijkstraAlgorithm.h"
#include "AbstractSearchAlgorithm.h"
#include <iostream>
#include <time.h>
#include <string>


inline GameState* ReadGameState(size_t fieldSize);
inline void PrintTestsOfAlgorithms(std::vector<AbstractSearchAlgorithm*> &algorithms, GameState* &gameStartState, GameRules &gameRules);
inline void PrintAlgorithmResult(AbstractSearchAlgorithm* &algorithm, GameState* &gameStartState, GameRules &gameRules);

int main()
{
	const size_t fieldSize = 4;
	GameState *gameStartState = ReadGameState(fieldSize);
	GameRules gameRules = GameRules(fieldSize);
	size_t inversionsCount = GameRules::CalculateInversionsCount(*gameStartState);
	if (inversionsCount % 2 == 0)
	{
		std::vector<AbstractSearchAlgorithm*> algorithms;
		BidirectBreadthFirstAlgorithm BidirectBreadthFirstAlgorithm;
		AStarAlgorithm aStarAlgorithm;
		BreadthFirstAlgorithm breadthFirstAlgortihm;
		DijkstraAlgorithm dijkstraAlgorithm;
		algorithms.push_back(&aStarAlgorithm);
		algorithms.push_back(&BidirectBreadthFirstAlgorithm);
		algorithms.push_back(&breadthFirstAlgortihm);
		algorithms.push_back(&dijkstraAlgorithm);
		AbstractSearchAlgorithm *currentAlgorithm = *(algorithms.begin());

		PrintAlgorithmResult(currentAlgorithm, gameStartState, gameRules);
		/* Uncomment it and comment upper line if you want to compare algorithms by their execution time*/
		//PrintTestsOfAlgorithms(algorithms, gameStartState, gameRules);
	}
	else
	{
		std::cout << inversionsCount << " is the number of inversions. Destination is unreachable.";
	}

	return 0;
}

inline GameState* ReadGameState(size_t fieldSize)
{
	std::vector<size_t> gameField = std::vector<size_t>(fieldSize * fieldSize);
	for (size_t index = 0; index < fieldSize * fieldSize - 1; ++index)
	{
		std::cin >> gameField[index];
	}
	int temp;
	std::cin >> temp;
	gameField[fieldSize * fieldSize - 1] = 0;
	GameState *gameState = new GameState();
	gameState->SetField(gameField);
	return gameState;
}


inline void PrintTestsOfAlgorithms(std::vector<AbstractSearchAlgorithm*> &algorithms, GameState* &gameStartState, GameRules &gameRules)
{
	int executionTime;
	for (std::vector<AbstractSearchAlgorithm*>::iterator currentAlgorithm = algorithms.begin(); currentAlgorithm != algorithms.end(); ++currentAlgorithm)
	{
		std::cout << (*currentAlgorithm)->ToString() << std::endl;
		executionTime = clock();
		std::vector<GameState> path = (*currentAlgorithm)->FindPath(gameRules, *gameStartState);
		executionTime = clock() - executionTime;
		std::cout << path.size() << " ";
		for (std::vector<GameState>::const_iterator currentState = path.begin(); currentState != path.end(); ++currentState)
		{
			std::cout << MoveDirectionToChar(currentState->GetMoveDirection()) << " ";
		}
		std::cout << std::endl << executionTime << " ms" << std::endl << std::endl;
	}
}

inline void PrintAlgorithmResult(AbstractSearchAlgorithm* &algorithm, GameState* &gameStartState, GameRules &gameRules)
{
	std::vector<GameState> path = algorithm->FindPath(gameRules, *gameStartState);
	std::cout << path.size() << " ";
	for (std::vector<GameState>::const_iterator currentState = path.begin(); currentState != path.end(); ++currentState)
	{
		std::cout << MoveDirectionToChar(currentState->GetMoveDirection()) << " ";
	}
}
