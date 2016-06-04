// ConnectFourANN.cpp : Definiert den Einstiegspunkt f�r die Konsolenanwendung.
//

#include "stdafx.h"

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <map>

#include "patternOutput.hpp"
#include "brett.hpp"
#include "ConnectFour.hpp"

#include "IniFile.h"

using namespace std;

	int main(int argc, char *argv[]) {
		CIniFile _iniFile = CIniFile();

		auto wert = _iniFile.GetRecord("TrainingDataYellow", "Training", argv[1]);
		patternOutput patternOutputYellow(&wert[0].Value);

		wert = _iniFile.GetRecord("TrainingDataRed", "Training", argv[1]);
		patternOutput patternOutputRed(&wert[0].Value);

		wert = _iniFile.GetRecord("SimulationOutput", "Simulation_01", argv[1]);
		ifstream infile(wert[0].Value);

		int Zeile = 0;

		string line = "";
		while (getline(infile, line)) {
			brett tempBrett = brett(7, 6);
			int spieler = 0;
			stringstream strstr(line);

			string number = "";
			getline(strstr, number, ';');

			string winner = "";
			getline(strstr, winner, ';');
			tempBrett.setWinner(stoi(winner));

			// Analyse result data
			int eingabe[42];
			string word = "";
			int iCount = 0;
			while (getline(strstr, word, ';'))
			{
				if (iCount < 42)
				{
					int position = stoi(word);
					if (position < 255)
					{
						tempBrett.addButton(position, spieler);
						spieler++;
						spieler = spieler % 2;
						eingabe[iCount] = stoi(word);
					}
					else
					{
						tempBrett.addButton(stoi(winner));
						break;
					}
					iCount++;
				}
			}
			tempBrett.outputTrainingString(&patternOutputYellow, 1);
			tempBrett.outputTrainingString(&patternOutputRed, 2);

			cout << "Ziele : " << Zeile++ << endl;
		}
		patternOutputRed.titelAusgabe();
		patternOutputYellow.titelAusgabe();
		patternOutputRed.commentAusgabe();
		patternOutputYellow.commentAusgabe();
		return 0;
};