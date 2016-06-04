#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <map>

#include "outputResult.hpp"
#include "collectResult.hpp"
#include "ConnectFour.hpp"
#include "Players.hpp"
#include "NeuralPlayer.hpp"
#include "IniFile.h"


class selectPlayer
{
	selectPlayer() { ;  }
	~selectPlayer() { ; }
	static std::shared_ptr<tlCF::Player>createPlayer(string name, string parameter);
};