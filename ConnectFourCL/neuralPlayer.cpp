
#include "NeuralPlayer.hpp"


#include "gsl_assert.h"
#include "ConnectFour.hpp"

#include <sstream>
#include <thread>
#include <chrono>

tlCF::NeuralPlayer::NeuralPlayer()
	/*: engine_(dev_())*/ {
	position = 0;
	neuralNet = NeuralNet::getInstance("C:\\work\\ConnectFour\\NeuralNets\\net01_yellow.mbn","C:\\work\\ConnectFour\\NeuralNets\\net01_red.mbn");
}

std::future<unsigned char> tlCF::NeuralPlayer::Play_Impl(BoardFieldStatus color, const BitBoard & board) {
	std::vector<bool> *statusThrow = new std::vector<bool>(board.collumn_count);
	int count = 0;
	for (int columnCount = 0; columnCount < board.collumn_count; columnCount++)
	{
		(*statusThrow)[columnCount] = board.CanThrowIn(columnCount);
		count++;
	}
	if (count == 0)
	{
		std::promise<unsigned char> promise;
		promise.set_value(0);
		return promise.get_future();
	}

	int position = neuralNet->getNextPosition(color, board, statusThrow);
	board.CanThrowIn(position);
	std::promise<unsigned char> promise;
	promise.set_value(position);
	return promise.get_future();
}
std::string tlCF::NeuralPlayer::GetName_Impl() const {
	return "NeuralPlayer";
}

std::string tlCF::NeuralPlayer::GetInitialState_Impl() const {
	return ("test");
}


