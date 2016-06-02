#pragma once

#include <fstream>
#include <ConnectFour.hpp>


/**
*/
class collectResult
{
	int _countRed;
	int _countYellow;
	int _countDraw;
public:
	collectResult();
	~collectResult();

	void sampleResult(tlCF::GameResult result);
	void outputResult();
};

