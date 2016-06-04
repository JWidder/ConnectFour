#include <string.h>
#include "collectResult.hpp"
#include <ConnectFour.hpp>
#include <string>
#include <map>
#include <sstream>

collectResult::collectResult(std::string name)
{
	_fileName = name;
	std::fstream filestream(_fileName, std::ios::out | std::ios::trunc);
	filestream.close();

	std::map<int, int> mapPlayer= std::map<int, int>();
}


collectResult::~collectResult()
{
}

void collectResult::sampleResult(tlCF::GameResult result)
{
	mapPlayer [(int)result.result]++;
}

void collectResult::outputResult()
{
	std::fstream filestream(_fileName, std::ios::app);
	filestream << "Ergebnisse" << std::endl;
	filestream << "Winner Yellow: " << mapPlayer[(int)tlCF::VictoryStatus::VictoryYellow] << std::endl;
	filestream << "Winner Red:    " << mapPlayer[(int)tlCF::VictoryStatus::VictoryRed] << std::endl;
	filestream << "No Winner:     " << mapPlayer[(int)tlCF::VictoryStatus::Draw] << std::endl;
	filestream.close();
}

std::string collectResult::outputStatus()
{
	std::stringstream _ss;

	_ss << "Yellow: " << mapPlayer[(int)tlCF::VictoryStatus::VictoryYellow];
	_ss << "Red:    " << mapPlayer[(int)tlCF::VictoryStatus::VictoryRed];
	_ss << "Draw:    " << mapPlayer[(int)tlCF::VictoryStatus::Draw] << std::endl;
	
	return _ss.str();
}

