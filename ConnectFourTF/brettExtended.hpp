#pragma once
#include "brett.hpp"
#include "snapshot.hpp"
#include "patternOutput.hpp"
#include <list>
#include <cstring>

namespace std
{
	class brettExtended : brett
	{
	public:

		brettExtended(int xLen, int yLen);
		virtual void addButton(int spalte, int wert);
		virtual void addButton(int status);
		virtual void setWinner(int winner);

		virtual int getCountSnapshots();
		virtual vector<int>getInput(int pos);
		virtual vector<int>getOutput(int pos);
		virtual void outputTrainingString(patternOutput * _patternOutput, int player);
	};
}