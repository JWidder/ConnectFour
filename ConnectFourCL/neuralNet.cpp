#include "neuralNet.hpp"

bool NeuralNet::instanceFlag = false;
NeuralNet* NeuralNet::single = NULL;
NeuralNet* NeuralNet::getInstance(const char *yellowNet, const char *redNet)
{
	if (!instanceFlag)
	{
		// Open the neural net
		int count = _MB_GetNetCount();
		auto test = _MB_LoadNet(yellowNet);
		_MB_AddNet();
		count = _MB_GetNetCount();
		_MB_SelectNet(1);
		test = _MB_LoadNet(redNet);

		single = new NeuralNet();
		instanceFlag = true;
		return single;
	}
	else
	{
		return single;
	}
}

int NeuralNet::getNextPosition(int player, const tlCF::BitBoard & board, std::vector<bool> *status)
{
	double maxWert = std::numeric_limits<double>::min();
	int maxPosition = std::numeric_limits<int>::min();

	auto test = _MB_SelectNet(player - 1);
	for (int rowCount = 0; rowCount < board.row_count; rowCount++)
	{
		for (int columnCount = 0; columnCount < board.collumn_count; columnCount++)
		{
			auto status = board.GetStatus(rowCount, columnCount);
			int pos = rowCount*board.collumn_count + columnCount;
			auto testApply = _MB_ApplyInputAct(pos, (double)status);
		}
	}
	_MB_ThinkStep();
	// Identify the next neuron
	for (int columnCount = 0; columnCount < board.collumn_count; columnCount++)
	{
		double value;
		_MB_GetOutputOut(columnCount, &value);
		if ((*status)[columnCount])
		{
			if (value < maxWert)
			{
				maxWert = value;
				maxPosition = columnCount;
			}
		}
	}
	// int position = _MB_GetOutputWinnerNeuron();
	return maxPosition;
}