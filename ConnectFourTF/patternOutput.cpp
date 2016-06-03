#include "stdafx.h"
#include "patternOutput.hpp"

using namespace std;

patternOutput::patternOutput(const char *fileName)
{
	titel = list<string>();
	comment= list<string>();
	ziel.open(fileName);
	if (!ziel) {
		std::cerr << "Datei kann nicht geöffnet werden!\n";
		exit(-1);
	}
	// formatiertes Schreiben
	ziel << "MemBrain V06.01.03.00" << std::endl;
	ziel << std::endl;
	ziel << "(Feb 11 2016)" << std::endl;
	ziel << "Sectioned CSV File" << std::endl;
	ziel << std::endl;
	ziel << "[<LESSON START>]" << std::endl;
	ziel << std::endl;
	ziel << "[<INFO HEADER>]" << std::endl;
	ziel << "This file represents a MemBrain Lesson." << std::endl;
	ziel << std::endl;
	ziel << "[<LESSON NAME>]" << std::endl;
	ziel << "New Lesson" << std::endl;
	ziel << std::endl;
	ziel << "[<LESSON COMMENT>]" << std::endl;
	ziel << "-- -" << std::endl;
	ziel << std::endl;
	ziel << "[<INPUTS>]" << std::endl;
	ziel << "IN_1_1; IN_1_2; IN_1_3; IN_1_4; IN_1_5; IN_1_6; IN_1_7; IN_2_1; IN 2.2; IN 2.3; IN 2.4; IN 2.5; IN 2.6; IN 2.7; IN 3.1; IN 3.2; IN 3.3; IN 3.4; IN 3.5; IN 3.6; IN 3.7; IN 4.1; IN 4.2; 24; 25; 26; 27; 28; 29; 30; 31; 32; 33; 34; 35; 36; 37; 38; 39; 40; 41; 42" << std::endl;
	ziel << std::endl;
	ziel << "[<OUTPUTS>]" << std::endl;
	ziel << "73; 72; 71; 70; 74; 75; 76" << std::endl;
	ziel << std::endl;
	ziel << "[<PATTERN FORMAT INFO>]" << std::endl;
	ziel << "IN_1_1; IN_1_2; IN_1_3; IN_1_4; IN_1_5; IN_1_6; IN_1_7; IN_2_1; IN 2.2; IN 2.3; IN 2.4; IN 2.5; IN 2.6; IN 2.7; IN 3.1; IN 3.2; IN 3.3; IN 3.4; IN 3.5; IN 3.6; IN 3.7; IN 4.1; IN 4.2; 24; 25; 26; 27; 28; 29; 30; 31; 32; 33; 34; 35; 36; 37; 38; 39; 40; 41; 42; 73; 72; 71; 70; 74; 75; 76" << std::endl;
	ziel << std::endl;
	ziel << "[<PATTERNS>]" << std::endl;
}


patternOutput::~patternOutput()
{
	ziel << "[<END>]" << std::endl;

	// Datei schließen, damit ziel wieder verwendet werden kann:
	ziel.close();
}

void patternOutput::outTrainingString(vector<int>* input, vector<int> *output)
{
	for (int i = 0; i < input->size(); i++)
	{
		ziel << (*input)[i] << " ; ";
	}
	int i;
	for (i = 0; i < output->size()-1; i++)
	{
		ziel << (*output)[i] << " ; ";
	}
	ziel << (*output)[i] << endl;

	titel.push_back("test");
	comment.push_back("comment");
}

void patternOutput::titelAusgabe()
{
	ziel << "[<PATTERN NAMES>]" << std::endl;
	for (std::list<string>::iterator it = titel.begin(); it != titel.end(); it++)
	{
		ziel << it->c_str() << endl;
	}
}

void patternOutput::commentAusgabe()
{
	ziel << "[<PATTERN COMMENTS>]" << std::endl;
	for (std::list<string>::iterator it = comment.begin(); it != comment.end(); it++)
	{
		ziel << it->c_str() << endl;
	}
}