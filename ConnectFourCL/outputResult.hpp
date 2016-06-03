#pragma once

#include <fstream>
#include <string>
#include <ConnectFour.hpp>


/**
*/
class outputResult
{
private:
	std::string _fileName;
public:
	outputResult(std::string *name);
	~outputResult();
	void writeResult(int iCount,tlCF::GameResult result);
};

