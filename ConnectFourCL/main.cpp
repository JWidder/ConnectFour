// ConnectFourANN.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

#include "outputResult.hpp"
#include "collectResult.hpp"
#include "ConnectFour.hpp"
#include "Players.hpp"

using namespace std;

int main() 
{
	outputResult _outputResult=outputResult();
	collectResult _collectResult = collectResult();

	auto yellowPlayer = std::make_shared<tlCF::MonteCarlo_SingleThreaded>(8000, tlCF::MonteCarlo_SingleThreadedStrategy::SimulationCount);
	auto redPlayer = std::make_shared<tlCF::MonteCarlo_SingleThreaded>(8000, tlCF::MonteCarlo_SingleThreadedStrategy::SimulationCount);

	int counter = 0;
	int countYellow = 0;
	int countRed = 0;
	int gesamt=100;

	auto game_ = std::make_unique<tlCF::Game>(yellowPlayer.get(), redPlayer.get());
	for (int i = 0; i < gesamt; i++)
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
				// ToDo wie rufe ich den Destruktor auf?
				cout << "Nr: " << i << " von " << gesamt << " yellow:" << countYellow << " red :" << countRed << endl;
			}
			countYellow = 0;
			countRed = 0;
			game_->Reset(true);
			for (int i = 0; i < gesamt; i++)
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
				// ToDo wie rufe ich den Destruktor auf?
				cout << "Nr: " << i << " von " << gesamt << " yellow:" << countYellow << " red :" << countRed << endl;
			}
			_collectResult.outputResult();
	int test;
	cin >> test;
	return 0;
};
