// ConnectFourANN.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

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
	auto sectionDaten = _iniFile.GetSection((string)"Player", argv[1]);
	auto recordRed = _iniFile.GetRecord("RedPlayer", "Player", argv[1]);
	auto recordYellow = _iniFile.GetRecord("YellowPlayer", "Player", argv[1]);
	auto anzahl = _iniFile.GetRecord("Number", "Simulation", argv[1]);
	int anzWerte = stoi(anzahl[0].Value);
	
	auto wert = _iniFile.GetRecord("SimulationOutput", "Files", argv[1]);
	std::string name= wert[0].Value.c_str();
	outputResult _outputResult = outputResult(&name);

	wert = _iniFile.GetRecord("SimulationOverview", "Files", argv[1]);
	const char *name1 = wert[0].Value.c_str();
	collectResult _collectResult = collectResult(name1);

	auto PlayerRandom = std::make_shared<tlCF::RandomPlayer>();
	auto PlayerMonteCarloNumber = std::make_shared<tlCF::MonteCarlo_SingleThreaded>(8000, tlCF::MonteCarlo_SingleThreadedStrategy::SimulationCount);
	auto PlayerMonteCarloTime500 = std::make_shared<tlCF::MonteCarlo_SingleThreaded>(500);
	auto PlayerMonteCarloTime2000 = std::make_shared<tlCF::MonteCarlo_SingleThreaded>(2000);
	auto PlayerNeural=std::make_shared<tlCF::NeuralPlayer>();

	std::hash<string> stringHash;
	wert = _iniFile.GetRecord("PlayerRed", "Simulation", argv[1]);
	string playerRed = wert[0].Value.c_str();
	int wertTest = stringHash(playerRed);
	wert = _iniFile.GetRecord("PlayerYellow", "Simulation", argv[1]);
	string playerYellow = wert[0].Value.c_str();
	wertTest = stringHash(playerYellow);

	std::map<string, std::shared_ptr<tlCF::Player>> mapPlayer;

	mapPlayer["MonteCaloTime500"] = std::make_shared<tlCF::MonteCarlo_SingleThreaded>(500);
	mapPlayer["MonteCaloTime2000"] = std::make_shared<tlCF::MonteCarlo_SingleThreaded>(2000);
	mapPlayer["MonteCaloNumber8000"] = std::make_shared<tlCF::MonteCarlo_SingleThreaded>(8000, tlCF::MonteCarlo_SingleThreadedStrategy::SimulationCount);
	mapPlayer["Random"] = std::make_shared<tlCF::RandomPlayer>();
	mapPlayer["Neural"] = std::make_shared<tlCF::NeuralPlayer>();

	// auto yellowPlayer = std::make_shared<tlCF::RandomPlayer>();
		// auto yellowPlayer = std::make_shared<tlCF::MonteCarlo_SingleThreaded>(8000, tlCF::MonteCarlo_SingleThreadedStrategy::SimulationCount);
		// auto redPlayer = std::make_shared<tlCF::MonteCarlo_SingleThreaded>(8000, tlCF::MonteCarlo_SingleThreadedStrategy::SimulationCount);
	// auto redPlayer = std::make_shared<tlCF::NeuralPlayer>();

	auto redPlayer = mapPlayer["MonteCaloTime500"];
	auto yellowPlayer = mapPlayer["MonteCaloTime500"];

	int counter = 0;
	int countYellow = 0;
	int countRed = 0;

	auto game_ = std::make_unique<tlCF::Game>(yellowPlayer.get(), redPlayer.get());
	for (int i = 0; i < anzWerte; i++)
	{
		counter++;
		auto result = game_->PlayGame();
		_collectResult.sampleResult(result);
		_outputResult.writeResult(counter,result);

		switch ((int)result.result)
				{
				case 1:
					countYellow++;
					break;
				case 2:
					countRed++;
					break;
				}
				game_->Reset(false);
				cout << "Nr: " << i << " von " << anzWerte<< " yellow:" << countYellow << " red :" << countRed << endl;
			}
			countYellow = 0;
			countRed = 0;
			game_->Reset(true);
			for (int i = 0; i < anzWerte; i++)
			{
				counter++;
				auto result = game_->PlayGame();
				_collectResult.sampleResult(result);
				_outputResult.writeResult(counter, result);

				switch ((int)result.result)
				{
				case 1:
					countYellow++;
					break;
				case 2:
					countRed++;
					break;
				}
				game_->Reset(false);
				cout << "Nr: " << i << " von " << anzWerte << " yellow:" << countYellow << " red :" << countRed << endl;
			}
			_collectResult.outputResult();
			cout << "Enter a value : ";
	int test;
	cin >> test;
	return 0;
};
