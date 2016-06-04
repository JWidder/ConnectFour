#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <map>

#include "outputResult.hpp"
#include "collectResult.hpp"
#include "ConnectFour.hpp"
#include "Players.hpp"
#include "NeuralPlayer.hpp"
#include "IniFile.h"

using namespace std;

std::shared_ptr<tlCF::Player> createPlayer(string name, string parameter)
{
	std::shared_ptr <tlCF::Player> tempPlayer;
	if (name == "MonteCarloTime")
	{
		int number = stoi(parameter);
		tempPlayer = std::make_shared<tlCF::MonteCarlo_SingleThreaded>(number);
	}
	else if (name == "MonteCarloNumber")
	{
		int number = stoi(parameter);
		tempPlayer = std::make_shared<tlCF::MonteCarlo_SingleThreaded>(number, tlCF::MonteCarlo_SingleThreadedStrategy::SimulationCount);
	}
	else if (name == "Random")
	{
		tempPlayer = std::make_shared<tlCF::RandomPlayer>();
	}
	else if (name == "Neural")
	{
		tempPlayer = std::make_shared<tlCF::NeuralPlayer>();
	}
	else
	{
		tempPlayer = std::make_shared<tlCF::RandomPlayer>();
	}

	return tempPlayer;
}


int main(int argc, char *argv[]) 
{
	CIniFile _iniFile = CIniFile();
	int anzWerte = stoi(_iniFile.GetRecord("Number", "Simulation_01", argv[1])[0].Value);
	
	outputResult _outputResult = outputResult(&_iniFile.GetRecord("SimulationOutput", "Simulation_01", argv[1])[0].Value);
	collectResult _collectResult = collectResult(_iniFile.GetRecord("SimulationOverview", "Simulation_01", argv[1])[0].Value);

	string playerRed = _iniFile.GetRecord("PlayerRed", "Simulation_01", argv[1])[0].Value;
	string playerRedParameter = _iniFile.GetRecord("PlayerRedNumber", "Simulation_01", argv[1])[0].Value;
	string playerYellow = _iniFile.GetRecord("PlayerYellow", "Simulation_01", argv[1])[0].Value;
	string playerYellowParameter = _iniFile.GetRecord("PlayerYellowNumber", "Simulation_01", argv[1])[0].Value;

	auto redPlayer = createPlayer(playerRed, playerRedParameter);
	auto yellowPlayer = createPlayer(playerYellow, playerYellowParameter);

	auto game_ = std::make_unique<tlCF::Game>(yellowPlayer.get(), redPlayer.get());
	for (int loopCount = 0; loopCount < anzWerte; loopCount++)
	{
		auto result = game_->PlayGame();
		_collectResult.sampleResult(result);
		_outputResult.writeResult(loopCount,result);

		game_->Reset(false);
		cout << _collectResult.outputStatus();
	}
	_collectResult.outputResult();
	cout << "Enter a value : ";
	int test;
	cin >> test;
	return 0;
};
