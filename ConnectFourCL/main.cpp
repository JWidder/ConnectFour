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

int main(int argc, char *argv[]) 
{
	CIniFile _iniFile = CIniFile();

	std::vector<string>iniDaten = std::vector<string>();
	iniDaten = _iniFile.GetSectionNames(argv[1]);
	auto anzahl = _iniFile.GetRecord("Number", "Simulation_01", argv[1]);
	int anzWerte = stoi(anzahl[0].Value);
	
	auto wert = _iniFile.GetRecord("SimulationOutput", "Simulation_01", argv[1]);
	std::string name= wert[0].Value.c_str();
	outputResult _outputResult = outputResult(&name);

	wert = _iniFile.GetRecord("SimulationOverview", "Simulation_01", argv[1]);
	const char *name1 = wert[0].Value.c_str();
	collectResult _collectResult = collectResult(name1);

	wert = _iniFile.GetRecord("PlayerRed", "Simulation_01", argv[1]);
	string playerRed = wert[0].Value.c_str();
	wert = _iniFile.GetRecord("PlayerRedNumber", "Simulation_01", argv[1]);
	int playerRedNumber = std::stoi(wert[0].Value);
	wert = _iniFile.GetRecord("PlayerYellow", "Simulation_01", argv[1]);
	string playerYellow = wert[0].Value.c_str();
	wert = _iniFile.GetRecord("PlayerYellowNumber", "Simulation_01", argv[1]);
	int playerYellowNumber = std::stoi(wert[0].Value);

	std::map<string, std::shared_ptr<tlCF::Player>> mapPlayer;
	mapPlayer["MonteCarloTime"] = std::make_shared<tlCF::MonteCarlo_SingleThreaded>(2000);
	mapPlayer["MonteCarloNumber"] = std::make_shared<tlCF::MonteCarlo_SingleThreaded>(8000, tlCF::MonteCarlo_SingleThreadedStrategy::SimulationCount);
	mapPlayer["Random"] = std::make_shared<tlCF::RandomPlayer>();
	mapPlayer["Neural"] = std::make_shared<tlCF::NeuralPlayer>();

	auto redPlayer = mapPlayer[playerRed];
	auto yellowPlayer = mapPlayer[playerYellow];

	std::map<int, int> distribution;

	auto game_ = std::make_unique<tlCF::Game>(yellowPlayer.get(), redPlayer.get());
	for (int loopCount = 0; loopCount < anzWerte; loopCount++)
	{
		auto result = game_->PlayGame();
		_collectResult.sampleResult(result);
		_outputResult.writeResult(loopCount,result);

		distribution[(int)result.result]++;
		game_->Reset(false);
		cout << _collectResult.outputStatus();
	}
	_collectResult.outputResult();
	cout << "Enter a value : ";
	int test;
	cin >> test;
	return 0;
};
