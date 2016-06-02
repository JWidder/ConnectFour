#pragma once

#include <list>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <iostream>

using namespace std;

	class patternOutput
	{
	private:
		ofstream ziel;
		list<string> titel;
		list<string> comment;

	public:
		patternOutput(const char *fileName);
		~patternOutput();

		void outTrainingString(vector<int> *input, vector<int> *output);
		void titelAusgabe();
		void commentAusgabe();
	};

