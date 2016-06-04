#include "selectPlayer.hpp"

std::shared_ptr<tlCF::Player> selectPlayer::createPlayer(string name, string parameter)
{
	std::shared_ptr <tlCF::Player> tempPlayer;
	if (name == "MonteCarloTime")
	{
		int number = stoi(parameter);
		tempPlayer= std::make_shared<tlCF::MonteCarlo_SingleThreaded>(number);
	}
	else if (name == "MonteCarloNumber")
	{
		int number = stoi(parameter);
		tempPlayer = std::make_shared<tlCF::MonteCarlo_SingleThreaded>(number, tlCF::MonteCarlo_SingleThreadedStrategy::SimulationCount);
	}
	else if (name == "Random")
	{
		tempPlayer= std::make_shared<tlCF::RandomPlayer>();
	}
	else if (name == "Neural")
	{
		tempPlayer= std::make_shared<tlCF::NeuralPlayer>();
	}
	else
	{
		tempPlayer= std::make_shared<tlCF::RandomPlayer>();
	}

	return tempPlayer;
}
