#include "stdafx.h"

#include "brettExtended.hpp"

namespace std
{
	brettExtended::brettExtended(int inXLen, int inYLen)  : brett(inXLen, inYLen)
	{
		/*
		xLen = inXLen;
		yLen = inYLen;
		_player = 0;
		werte = list<snapshot>();
		werte.push_back(snapshot(xLen, yLen));
		*/
		return;
	}

	/**
	Eintragene eines neuen Moduls
	*/
	void brettExtended::addButton(int spalte, int wert)
	{
		pointSnapshot = &werte.back();
		pointSnapshot->setModule(spalte);
		pointSnapshot = &werte.back();
		werte.push_back(*pointSnapshot);
		pointSnapshot = &werte.back();
		pointSnapshot->addButton(spalte, wert);
		_player = (_player + 1) % 2;
		pointSnapshot->setPlayer(_player + 1);
	}

	void brettExtended::addButton(int status)
	{
		pointSnapshot = &werte.back();
		pointSnapshot->setStatus(status);
	}

	void brettExtended::setWinner(int winner)
	{
		_winner = winner;
	}

	int brettExtended::getCountSnapshots()
	{
		return (int)werte.size();
	}

	vector<int> brettExtended::getInput(int pos)
	{
		list<snapshot>::iterator zeiger = werte.begin();
		for (int i = 0; i < pos - 1; i++)
		{
			zeiger++;
		}
		return zeiger->getBoardInput();
	}

	vector<int> brettExtended::getOutput(int pos)
	{
		list<snapshot>::iterator zeiger = werte.begin();
		for (int i = 0; i < pos - 1; i++)
		{
			zeiger++;
		}
		return zeiger->getBoardOutput();
	}

	void brettExtended::outputTrainingString(patternOutput *_patternOutput, int player)
	{
		if (_winner == player)
		{
			for (list<snapshot>::iterator zeiger = werte.begin(); zeiger != werte.end(); ++zeiger)
			{
				if ((*zeiger).getPlayer() == player)
				{
					_patternOutput->outTrainingString((*zeiger).getBoardData(), (*zeiger).getModulData());
				}
			}
		}
	}
}
