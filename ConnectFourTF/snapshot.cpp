#include "stdafx.h"

#include "snapshot.hpp"

using namespace std;

snapshot::snapshot(int inXLen, int inYLen)
{
	xLen = inXLen;
	yLen = inYLen;
	snapshotBoard = vector<int>(xLen*yLen);
	snapshotOutput = vector<int>(xLen);
}

snapshot::snapshot(const snapshot & oldSnapshot)
	:xLen(oldSnapshot.xLen),
	yLen(oldSnapshot.yLen),
	snapshotBoard(oldSnapshot.snapshotBoard)
{
	snapshotOutput = vector<int>(xLen);
}


void snapshot::addButton(int spalte, int wert)
{
	for (int row = 0; row < yLen; row++)
	{
		int position = row*xLen + spalte;
		if (snapshotBoard[position] == 0)
		{
			snapshotBoard[position] = wert + 1;
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
