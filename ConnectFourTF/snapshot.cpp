#include "stdafx.h"

#include "snapshot.hpp"

using namespace std;

int std::snapshot::calculatePosition(int row, int column)
{
	return row*xLen + column;
}

snapshot::snapshot(int inXLen, int inYLen)
{
	xLen = inXLen;
	yLen = inYLen;
	snapshotBoard = vector<int>(xLen*yLen);
	snapshotOutput = vector<int>(xLen);

	snapshotVertical = vector<int>(xLen*yLen);
	snapshotLeft = vector<int>(xLen*yLen);
	snapshotRight = vector<int>(xLen*yLen);

}

snapshot::snapshot(const snapshot & oldSnapshot)
	:xLen(oldSnapshot.xLen),
	yLen(oldSnapshot.yLen),
	snapshotBoard(oldSnapshot.snapshotBoard)
{
	snapshotOutput = vector<int>(xLen);
}



void snapshot::addButton(int spalte, int player)
{
	for (int row = 0; row < yLen; row++)
	{
		int position = calculatePosition(row,spalte);
		if (snapshotBoard[position] == 0)
		{
			player = player + 1;
			snapshotBoard[position] = player;
			snapshotVertical[position] = checkVertical(player, row, spalte);
			snapshotVertical[position] = checkLeft(player,row, spalte);
			snapshotVertical[position] = checkRight(player,row, spalte);
			return;
		}
	}
}

vector<int> snapshot::getBoardInput()
{
	return snapshotBoard;
}
vector<int> snapshot::getBoardOutput()
{
	return snapshotOutput;
}

void snapshot::setModule(int button)
{
	modul = button;
	snapshotOutput[button] = 1;
}

void std::snapshot::setStatus(int inStatus)
{
	status = inStatus;
}

void std::snapshot::setPlayer(int player)
{
	_player = player;
}

int std::snapshot::getPlayer()
{
	return _player;
}

vector<int> *std::snapshot::getBoardData()
{
	return &snapshotBoard;
}

vector<int> *std::snapshot::getModulData()
{
	return &snapshotOutput;
}

double std::snapshot::checkVertical(int player,int column, int row)
{
	if ((row + 4) >= yLen) {
		return -1.0;
	}
	player = player + 1;
	double wert = 0.25;
	for (int iCount = 0; iCount < 4; ++iCount)
	{
		int position = calculatePosition(row+iCount, column);
		int positionNext = calculatePosition(row+1+iCount, column);
		int modulBasis = snapshotBoard[position];
		int modulNext = snapshotBoard[positionNext];
		if ((modulBasis == player) && (modulNext == player)) // Sequence of two equal Elements
		{
			wert *= 2;
		}
		else if ((modulBasis == player) && (modulNext == 0)) // Filling sequence possible
		{
			break;
		}
		else
		{
			wert = 0;
			break;
		}
	}
	return wert;
}

double std::snapshot::checkLeft(int player, int column, int row)
{
	if ((row + 4) >= yLen) {
		return -1.0;
	}
	if (column <3) {
		return -1.0;
	}
	double wert = 0.25;
	for (int iCount = 0; iCount < 4; ++iCount)
	{
		int position = calculatePosition(row, column);
		int positionNext = calculatePosition(row + 1, column-1);
		int modulBasis = snapshotBoard[position];
		int modulNext = snapshotBoard[positionNext];
		if ((modulBasis == player) && (modulNext == player))
		{
			wert *= 2;
		}
		else if ((modulBasis == player) && (modulBasis == player))
		{
			break;
		}
		else
		{
			wert = 0;
			break;
		}
	}
	return wert;
}

double std::snapshot::checkRight(int player, int column, int row)
{
	if ((row + 4) >= yLen) {
		return -1.0;
	}
	double wert = 0.25;
	for (int iCount = 0; iCount < 4; ++iCount)
	{
		int position = calculatePosition(row, column);
		int positionNext = calculatePosition(row + 1, column);
		int modulBasis = snapshotBoard[position];
		int modulNext = snapshotBoard[positionNext];
		if ((modulBasis == player) && (modulNext == player))
		{
			wert *= 2;
		}
		else if ((modulBasis == player) && (modulBasis == player))
		{
			break;
		}
		else
		{
			wert = 0;
			break;
		}
	}
	return wert;
}

double std::snapshot::checkDirection(searchDirection direction, int player, int column, int row)
{
	if ((row + 4) >= yLen) {
		return -1.0;
	}


	int _stepVertical;
	int _stepHorizontal;
	switch (direction)
	{
	case vertical:
		_stepVertical=1;
		_stepHorizontal=0;
		break;
	case left:
		if ((row + 4) >= yLen) {
			return -1.0;
		}
		_stepVertical = 1;
		_stepHorizontal = -1;
		break;
	case right:
		if ((row + 4) >= yLen) {
			return -1.0;
		}
		_stepVertical = 1;
		_stepHorizontal = 1;
		break;
	default:
		break;
	}
	double wert = 0.25;
	for (int iCount = 0; iCount < 4; ++iCount)
	{
		int position = calculatePosition(row, column);
		int positionNext = calculatePosition(row + 1, column);
		int modulBasis = snapshotBoard[position];
		int modulNext = snapshotBoard[positionNext];
		if ((modulBasis == player) && (modulNext == player))
		{
			wert *= 2;
		}
		else if ((modulBasis == player) && (modulBasis == player))
		{
			break;
		}
		else
		{
			wert = 0;
			break;
		}
	}
	return wert;
}
