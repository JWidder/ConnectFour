// ConnectFourANN.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

#include "patternOutput.hpp"
#include "brett.hpp"

using namespace std;

	int main() {
		int resultRed = 0;
		int resultYellow = 0;
		int resultDraw = 0;
		patternOutput patternOutput("c:\\temp\\ausgabe.csv");
		int Zeile = 0;
		ifstream infile("C://temp//daten.csv"); // for example
		string line = "";
		while (getline(infile, line)) {
			brett tempBrett = brett(7, 6);
			int spieler = 0;
			stringstream strstr(line);

			string number = "";
			getline(strstr, number, ';');

			string winner = "";
			getline(strstr, winner, ';');
			switch (stoi(winner))
			{
			case 1: 
				resultYellow++;
				break;
			case 2:
				resultRed++;
				break;
			case 3:
				resultDraw++;
				break;
			}

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
			tempBrett.outputTrainingString(&patternOutput);

			cout << "Ziele : " << Zeile++ << endl;
		}
		cout << "yellow: " << resultYellow << " red = " << resultRed << " draw = " << resultDraw << endl;
		patternOutput.titelAusgabe();
		patternOutput.commentAusgabe();
		return 0;
};
