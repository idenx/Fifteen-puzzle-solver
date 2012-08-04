#pragma once

enum moveDirections
{
	LEFT = 0,
	UP = 1,
	DOWN = 2,
	RIGHT = 3,
	EMPTY = 4
};

inline moveDirections InvertMoveDirection(moveDirections currentDirection)
{
	return (moveDirections)(3 - (int)currentDirection);
}

inline char MoveDirectionToChar(moveDirections currentDirection)
{
	switch(currentDirection)
	{
	case DOWN:
		return 'v';
	case UP:
		return '^';
	case LEFT:
		return '<';
	case RIGHT:
		return '>';
	}
	return 0;
}
