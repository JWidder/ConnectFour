#include "stdafx.h"

#include "brett.hpp"

namespace std
{
	brett::brett(int inXLen, int inYLen)
	{
		xLen = inXLen;
		yLen = inYLen;
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
	}

	void brett::addButton(int status)
	{
		pointSnapshot = &werte.back();
		pointSnapshot->setStatus(status);
	}


	int brett::getCountSnapshots()
	{
		return werte.size();
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

	void brett::outputTrainingString(patternOutput *_patternOutput)
	{
		for (list<snapshot>::iterator zeiger = werte.begin(); zeiger != werte.end(); ++zeiger)
		{
			_patternOutput->outTrainingString((*zeiger).getBoardData(), (*zeiger).getModulData());
		}
	}
}
