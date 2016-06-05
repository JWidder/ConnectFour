#pragma once

#include "brett.hpp"
#include "snapshot.hpp"
#include "patternOutput.hpp"
#include <list>
#include <cstring>

namespace std
{
	class brettBasis : public brett
	{
	public:
		brettBasis(int xLen, int yLen);
		virtual vector<int>getInput(int pos);
		virtual vector<int>getOutput(int pos);
		virtual void outputTrainingString(patternOutput * _patternOutput, int player);
	};
}