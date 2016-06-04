#pragma once
#include <iostream> 
#include <stdlib.h> 
#include "ConnectFour.hpp"

#include "../DLL/MemBrain_inc.h"

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
	static NeuralNet* getInstance(std::string netName);
	int getNextPosition(int player, const tlCF::BitBoard & board, std::vector<bool> *status);
	~NeuralNet()
	{
		instanceFlag = false;
	}
	int count = 0;
};