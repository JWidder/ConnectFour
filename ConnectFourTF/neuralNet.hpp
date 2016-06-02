#pragma once
#include <iostream> 
#include <stdlib.h> 
#include "ConnectFour.hpp"

#include "MemBrain_inc.h"

class NeuralNet
{
private:
	static bool instanceFlag;
	static NeuralNet *single;
	NeuralNet()
	{
		//private constructor
	}
public:
	static NeuralNet* getInstance(const char *yellowNet,const char *redNet);
	int getNextPosition(int player, const tlCF::BitBoard & board);
	~NeuralNet()
	{
		instanceFlag = false;
	}
	int count = 0;
};