#pragma once
#include "ConnectFour.hpp"

#include <random>
#include <thread>
#include <memory>
#include <string>
#include "neuralNet.hpp"

namespace tlCF {

	class NeuralPlayer : public Player {
	public:
		NeuralPlayer() { ; }
		NeuralPlayer(std::string netName);
	private:
		int position;
		NeuralNet *neuralNet;
		// Inherited via Player
		virtual std::future<unsigned char> Play_Impl(BoardFieldStatus color, const BitBoard & board) override final;
		virtual std::string GetName_Impl() const override final;
		std::string GetInitialState_Impl() const override final;
	};
}