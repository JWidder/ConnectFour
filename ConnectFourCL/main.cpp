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
#include "selectPlayer.hpp"

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

//	std::vector<string>iniDaten = std::vector<string>();
//	iniDaten = _iniFile.GetSectionNames(argv[1]);

	int anzWerte = stoi(_iniFile.GetRecord("Number", "Simulation_01", argv[1])[0].Value);
	
	auto wert = _iniFile.GetRecord("SimulationOutput", "Simulation_01", argv[1]);
	std::string name= wert[0].Value;
	outputResult _outputResult = outputResult(&name);

	wert = _iniFile.GetRecord("SimulationOverview", "Simulation_01", argv[1]);
	const char *name1 = wert[0].Value.c_str();
	collectResult _collectResult = collectResult(name1);

	wert = _iniFile.GetRecord("PlayerRed", "Simulation_01", argv[1]);
	string playerRed = wert[0].Value.c_str();
	wert = _iniFile.GetRecord("PlayerRedNumber", "Simulation_01", argv[1]);
	int playerRedNumber = std::stoi(wert[0].Value);
	string playerRedParameter = wert[0].Value;
	wert = _iniFile.GetRecord("PlayerYellow", "Simulation_01", argv[1]);
	string playerYellow = wert[0].Value.c_str();
	wert = _iniFile.GetRecord("PlayerYellowNumber", "Simulation_01", argv[1]);
	int playerYellowNumber = std::stoi(wert[0].Value);
	string playerYellowParameter = wert[0].Value;

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
