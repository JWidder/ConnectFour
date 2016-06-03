#pragma once

#include <fstream>
#include <string>
#include <ConnectFour.hpp>


/**
*/
class collectResult
{
	std::string _fileName;
	int _countRed;
	int _countYellow;
	int _countDraw;
public:
	collectResult(std::string name);
	~collectResult();

	void sampleResult(tlCF::GameResult result);
	void outputResult();
};

