#include <string.h>
#include "collectResult.hpp"




collectResult::collectResult(std::string name)
{
	_fileName = name;
	_countDraw = 0;
	_countRed = 0;
	_countYellow = 0;
	std::fstream filestream(_fileName, std::ios::out | std::ios::trunc);
	filestream.close();
}


collectResult::~collectResult()
{
}

void collectResult::sampleResult(tlCF::GameResult result)
{
	switch (result.result)
	{
	case tlCF::VictoryStatus::Draw:
		_countDraw++;
		break;
	case tlCF::VictoryStatus::VictoryRed:
		_countRed++;
		break;
	case tlCF::VictoryStatus::VictoryYellow:
		_countYellow++;
		break;
	}
}

void collectResult::outputResult()
{
	std::fstream filestream(_fileName, std::ios::app);
	filestream << "Ergebnisse" << std::endl;
	filestream << "Winner Yellow: " << _countYellow << std::endl;
	filestream << "Winner Red:    " << _countRed << std::endl;
	filestream << "No Winner:     " << _countDraw << std::endl;
	filestream.close();
}
