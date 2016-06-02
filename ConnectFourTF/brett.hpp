#pragma once
#include "snapshot.hpp"
#include <list>
#include <cstring>

namespace std
{
	class brett
	{
	private:

		int drawModul;
		int xLen;
		int yLen;
		list<snapshot> werte;
		snapshot *pointSnapshot;

	public:

		brett(int xLen, int yLen);
		void addButton(int spalte, int wert);
		void addButton(int status);

		int getCountSnapshots();
		vector<int>getInput(int pos);
		vector<int>getOutput(int pos);
	};
}