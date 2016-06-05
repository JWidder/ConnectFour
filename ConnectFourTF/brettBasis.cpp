#include "stdafx.h"

#include "brettBasis.hpp"

namespace std
{
	brettBasis::brettBasis(int inXLen, int inYLen) : brett(inXLen, inYLen)
	{
		return;
	}

	vector<int> brettBasis::getInput(int pos)
	{
		list<snapshot>::iterator zeiger=werte.begin();
		for (int i = 0; i < pos-1; i++)
		{
			zeiger++;
		}
		return zeiger->getBoardInput();
	}

	vector<int> brettBasis::getOutput(int pos)
	{
		list<snapshot>::iterator zeiger = werte.begin();
		for (int i = 0; i < pos - 1; i++)
		{
			zeiger++;
		}
		return zeiger->getBoardOutput();
	}

	void brettBasis::outputTrainingString(patternOutput *_patternOutput,int player)
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
