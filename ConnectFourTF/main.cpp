// ConnectFourANN.cpp : Definiert den Einstiegspunkt f�r die Konsolenanwendung.
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
		int winnerRed = 0;
		int winnerYellow = 0;
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
				winnerYellow++;
				break;
			case 2:
				winnerRed++;
				break;
			}

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
						tempBrett.addButton(position, spieler++);
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
			for (int iCount = 0; iCount < tempBrett.getCountSnapshots(); iCount++)
			{
				patternOutput.outTrainingString(&tempBrett.getInput(iCount),&tempBrett.getOutput(iCount));
			}

			cout << "Ziele : " << Zeile++ << endl;
		}
		cout << "yellow: " << winnerYellow << " red = " << winnerRed << endl;
		int test;
		cin >> test;
		patternOutput.titelAusgabe();
		patternOutput.commentAusgabe();
		return 0;
};
