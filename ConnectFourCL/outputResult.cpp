#include "outputResult.hpp"
#include <string>

outputResult::outputResult(std::string *name)
{
_fileName=*name;
std::fstream filestream(_fileName, std::ios::out | std::ios::trunc);
filestream.close();
}

outputResult::~outputResult()
{
}

void outputResult::writeResult(int iCount,tlCF::GameResult result)
{
	std::fstream filestream(_fileName, std::ios::app);
	filestream << iCount << " ; " << (int)result.result << " ; ";
	for (int iCount = 0; iCount < 42; iCount++)
	{
		filestream << (int)result.moves[iCount] << " ; ";
	}
	filestream << std::endl;
	filestream.close();
}
