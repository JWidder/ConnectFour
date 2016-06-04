#pragma once

#include <fstream>
#include <string>
#include <map>
#include <ConnectFour.hpp>


/**
*/
class collectResult
{
	std::string _fileName;
	std::map<int, int> mapPlayer;
public:
	collectResult(std::string name);
	~collectResult();

	void sampleResult(tlCF::GameResult result);
	void outputResult();
	std::string outputStatus();
};

