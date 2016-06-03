#pragma once
#include <vector>

namespace std
{
	class snapshot
	{
	private:
		int xLen;
		int yLen;
		int modul;
		int status;
		int _player;
		vector<int> snapshotBoard;
		vector<int> snapshotOutput;
	public:
		snapshot(int xLen,int yLen);
		snapshot(const snapshot & snapshot);
		void addButton(int xWert, int yWert);
		vector<int>getBoardOutput();
		vector<int>getBoardInput();
		void setModule(int button);
		void setStatus(int inStatus);
		void setPlayer(int player);
		int getPlayer();
		vector<int> *getBoardData();
		vector<int> *getModulData();
	};
}