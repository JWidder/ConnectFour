#include "stdafx.h"

#include "brett.hpp"

namespace std
{
	brett::brett(int inXLen, int inYLen)
	{
		xLen = inXLen;
		yLen = inYLen;
		_player = 0;
		werte = list<snapshot>();
		werte.push_back(snapshot(xLen, yLen));
	}

	/**
	Eintragene eines neuen Moduls
	*/
	void brett::addButton(int spalte, int wert)
	{
		pointSnapshot = &werte.back();
		pointSnapshot->setModule(spalte);
		pointSnapshot = &werte.back();
		werte.push_back(*pointSnapshot);
		pointSnapshot = &werte.back();
		pointSnapshot->addButton(spalte, wert);
		_player = (_player + 1) % 2;
		pointSnapshot->setPlayer(_player+1);
	}

	void brett::addButton(int status)
	{
		pointSnapshot = &werte.back();
		pointSnapshot->setStatus(status);
	}

	void brett::setWinner(int winner)
	{
		_winner = winner;
	}

	int brett::getCountSnapshots()
	{
		return (int)werte.size();
	}

	vector<int> brett::getInput(int pos)
	{
		list<snapshot>::iterator zeiger=werte.begin();
		for (int i = 0; i < pos-1; i++)
		{
			zeiger++;
		}
		return zeiger->getBoardInput();
	}

	vector<int> brett::getOutput(int pos)
	{
		list<snapshot>::iterator zeiger = werte.begin();
		for (int i = 0; i < pos - 1; i++)
		{
			zeiger++;
		}
		return zeiger->getBoardOutput();
	}

	void brett::outputTrainingString(patternOutput *_patternOutput,int player)
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
