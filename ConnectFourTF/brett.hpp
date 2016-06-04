#pragma once
#include "snapshot.hpp"
#include "patternOutput.hpp"
#include <list>
#include <cstring>

namespace std
{
	class brett
	{
	private:

		// int drawModul;
		int xLen;
		int yLen;
		int _winner;
		int _player;
		list<snapshot> werte;
		snapshot *pointSnapshot;

	public:

		brett(int xLen, int yLen);
		void addButton(int spalte, int wert);
		void addButton(int status);
		void setWinner(int winner);

		int getCountSnapshots();
		vector<int>getInput(int pos);
		vector<int>getOutput(int pos);
		void outputTrainingString(patternOutput * _patternOutput, int player);
	};
}